

#include <stdio.h>
#include "typedefs.h"
#include "../../functional/hal/hal_ethernet.h"
#include "lib_ethernet_p.h"
#include "os/os_alarm.h"
STATIC void Lib_Ethernet_SendPacket( Lib_Ethernet_Self *self );

/*
3.) Network Application
    a.) While the button is pushed, a UDP socket shall be opened with a server at the domain "test.ring.com" on port 13469. Every 1 second, the device shall send a packet of 2 bytes to the server with a counter, starting at value 0 and increasing by 1 every packet.
    b.) For every 2-byte UDP packet sent to the server, the server shall return back a 2-byte packet on the same port echoing the counter. If no echo is received within 500ms or the value returned from the server is not equal to the value sent from the device, the device shall re-send the current value. This shall continue until the correct value is received from the server, at which point the device will increment the counter and proceed as normal.
    c.) When the button is released, the socket shall be closed and the counter shall be reset.
*/
void Lib_Ethernet_CreateSelf( struct Lib_Ethernet_Self *self, HAL_Ethernet_Self *halEthernet )
{
    if ( self != NULL )
    {        
        self->count = 0;
        self->halEthernet = halEthernet;
        self->time = 0;
        self->running = FALSE;
    }
}
/*
    This function will trigger if the transmission/reception process has failed, or it has taken longer than 500 to complete
*/
STATIC void Lib_Ethernet_SendTimeOut( Lib_Ethernet_Self *self)
{
  
    //this doesnt update count
    //set an alarm that will call Lib_Ethernet_StartSendingProcess in the time difference between the last time we checked time and now.
    //alarm_set( Lib_Ethernet_StartSendingProcess, self, (current_time_in_miliseconds) - self->time );
    //500 ms have elapsed an we havent reive anything
    //wait for a remaining 500 ms,  and send the same packet
    OS_Alarm_Set( (Event) Lib_Ethernet_StartSendingProcess, self, OS_ALARM_SECONDS_TO_BEATS( 1 ) - ( HAL_Time_GetBeatsSinceStartup() - self->time ) );

}

STATIC void Lib_Ethernet_SendProcessCompletedCallback( Lib_Ethernet_Self *self )
{
    if( self != NULL )
    {
        //cancel time out since we receved a packet
        OS_Alarm_Cancel( (Event) Lib_Ethernet_SendTimeOut, self );

        UINT8 incPacket[PACKET_SIZE];
        //cancel timeout alarm
        //if this function is called the process was completed successfully
        //and there is a reply from the server
        if( Hal_EthernetGetIncomingPacket( self->halEthernet, incPacket, PACKET_SIZE ) )
        {
            UINT32 i;

            UINT16 incValue = (UINT16)( (UINT16)(incPacket[0]) | ((UINT16)(incPacket[1]) << 8) );
            if( self->count == incValue )
            {
                //update count
                self->count++;
            }       
        }
        //we would resend the same value if the incoming packet failed, or didnt match
        //set an alarm that will call Lib_Ethernet_StartSendingProcess in the time difference between the last time we 
        //checked time and now.
        //alarm_set( Lib_Ethernet_StartSendingProcess, self, 
        //OS_ALARM_MILISECONDS_TO_BEATS(current_time_in_miliseconds) - self->time );
        //we are supposed to send another packet every 1 second
        //some time thqt is less than 500 ms but more than 0 has elapsed
        //set an alarm that fires at 1 second - time elapsed. 
        if( self->running == TRUE )
        {
            OS_Alarm_Set( (Event) Lib_Ethernet_SendPacket, self, OS_ALARM_SECONDS_TO_BEATS( 1 ) - ( HAL_Time_GetBeatsSinceStartup() - self->time ) );
        }
    }
}
STATIC void Lib_Ethernet_SendPacket( Lib_Ethernet_Self *self )
{
    if( self != NULL )
    {
        UINT8 packet[PACKET_SIZE];
        //little endian
        packet[0] = (UINT8)(self->count);     //LSB
        packet[1] = (UINT8)(self->count >> 8); //MSB
        //self->time = save the current time, in beats
        self->time = HAL_Time_GetBeatsSinceStartup();
        
        Hal_Ethernet_SendThenReceivePacket( self->halEthernet, packet, PACKET_SIZE, (HAL_Ethernet_TxCompletedCallback)Lib_Ethernet_SendProcessCompletedCallback, self );
        //set an alarm to wait for the time out time of 500ms
        //alarm_set( Lib_Ethernet_SendTimeOut, self, 500 )
        OS_Alarm_Set( (Event) Lib_Ethernet_SendTimeOut, self, OS_ALARM_MILISECONDS_TO_BEATS( 500 ) );
    }

}
void STATIC Lib_Ethernet_ResetToStartingState( Lib_Ethernet_Self *self )
{
    if( self != NULL )
    {
        //stop on going timers
        OS_Alarm_Cancel( (Event) Lib_Ethernet_SendTimeOut, self );
        OS_Alarm_Cancel( (Event) Lib_Ethernet_SendPacket, self );
        //tell hal to stop sending whatever it was sending.
        HAL_Ethernet_CloseUDPPort( self->halEthernet );
        //reset counter
        self->count = 0;

    }
}
void Lib_Ethernet_StartSendingProcess( Lib_Ethernet_Self *self )
{
    if( self != NULL )
    {
        self->running = TRUE;
        //reset to starting state
        Lib_Ethernet_ResetToStartingState( self );

        HAL_Ethernet_OpenUDPPort( self->halEthernet );// the port and server name was already set during setup

        Lib_Ethernet_SendPacket( self );
    }
}

void Lib_Ethernet_StopSendingProcess( Lib_Ethernet_Self *self )
{
    if( self != NULL )
    {
        self->running = FALSE;
        Lib_Ethernet_ResetToStartingState( self );
    }
}
