#include "typedefs.h"
#include "hal_ethernet_p.h"
#include <stdio.h>
#include <string.h>

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
        memcpy( incPacket, self->incomingPacket, maxLength);
        toReturn = TRUE;
    }
    return toReturn;
}
void HAL_Ethernet_OpenUDPPort( struct HAL_Ethernet_Self *self )
{
    if( self != NULL )
    {
        printf("Openning Server %s:%u\r\n", self->serverName, self->serverPort);
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
    }
}
void Hal_Ethernet_SendThenReceivePacket( struct HAL_Ethernet_Self *self, UINT8 *outPacket, UINT32 packetSize, void ( *txCompletedCallback )( void *delegate) , void *delegate )
{
    if( self != NULL )
    {   
        /*this can be extracted onto a helper function*/
        UINT32 i;
        printf("Sending [ ");
        for( i = 0; i<packetSize; i++)
        {
            printf("%02X ", outPacket[i]);
        }
        printf("]\r\n");

        /*
        this drive should send the needed packet and read the respones
        */     
        memcpy( self->incomingPacket, outPacket, packetSize);
        /*
            call the completion callback everytime.
            this is mocked behavior of the packet being sent and received
        */
        if( txCompletedCallback != NULL )
        {
            txCompletedCallback( delegate );
        }
    }
}
