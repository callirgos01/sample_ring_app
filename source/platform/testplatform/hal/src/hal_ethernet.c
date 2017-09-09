#include "typedefs.h"
#include "hal_ethernet_p.h"
#include <stdio.h>
#include <string.h>
//this dependency is being added ONLY for the purposes of simulating hardware events
//on a real application we would never have HAL be dependent on OS
#include "os/os_alarm.h"
void HAL_Ethernet_CreateSelf( struct HAL_Ethernet_Self *self )
{
    if( self != NULL )
    {
        memset(self->serverName, 0, MAX_SERVER_NAME_SIZE);
        self->serverPort = 0;
    }

}

void HAL_Ethernet_Configure( struct HAL_Ethernet_Self *self, char *serverName, UINT32 serverNameLength, UINT32 serverPort )
{
    if( self != NULL )
    {
        memcpy(self->serverName, serverName, serverNameLength);
        self->serverPort = serverPort;        
    }
}
BOOLEAN Hal_EthernetGetIncomingPacket( struct HAL_Ethernet_Self *self, UINT8 *incPacket, UINT32 maxLength )
{
    BOOLEAN toReturn = FALSE;
    if( self != NULL )
    {
        UINT32 i;
        DPrintf("Rx [ ");
        for( i = 0; i<maxLength; i++)
        {
            printf("%02X ", self->incomingPacket[i]);
        }
        printf("]\r\n");

        memcpy( incPacket, self->incomingPacket, maxLength);
        toReturn = TRUE;
    }
    return toReturn;
}
void HAL_Ethernet_OpenUDPPort( struct HAL_Ethernet_Self *self )
{
    if( self != NULL )
    {
        DPrintf("Openning Server %s:%u\r\n", self->serverName, self->serverPort);
        /*
            this driver shall open the port
        */
    }
}
void HAL_Ethernet_CloseUDPPort( struct HAL_Ethernet_Self *self )
{
    if( self != NULL )
    {
        /*
            this driver shall close the port
        */
        printf("closing port\r\n");
    }
}
STATIC void HAL_Ethernet_TxCompleted( struct HAL_Ethernet_Self *self )
{
    if( self != NULL )
    {
        if( self->txCompletedCallback != NULL )
        {
            self->txCompletedCallback( self->delegate );
        }
    }

}
void Hal_Ethernet_SendThenReceivePacket( struct HAL_Ethernet_Self *self, UINT8 *outPacket, UINT32 packetSize, void ( *txCompletedCallback )( void *delegate) , void *delegate )
{
    if( self != NULL )
    {   
        /*this can be extracted onto a helper function*/
        UINT32 i;
        DPrintf("Tx [ ");
        for( i = 0; i<packetSize; i++)
        {
            printf("%02X ", outPacket[i]);
        }
        printf("]\r\n");

        /*
        this driver should send the needed packet and read the respones
        */
        //simulate a delayed response, by setting an alarm that will call the response function after some time.
        //this can be used to test the host time out of the calling code. 



        memcpy( self->incomingPacket, outPacket, packetSize);
        
        self->txCompletedCallback = txCompletedCallback;
        self->delegate = delegate;
        //this would be replaced by a call to the hardware
        OS_Alarm_Set( (Event) HAL_Ethernet_TxCompleted, self, OS_ALARM_MILISECONDS_TO_BEATS( 250 ) );
    }
}
