#ifndef HAL_ETHERNET_H
#define HAL_ETHERNET_H

typedef struct HAL_Ethernet_Self HAL_Ethernet_Self;
typedef void ( *HAL_Ethernet_TxCompletedCallback )( void *delegate);
void HAL_Ethernet_Configure( HAL_Ethernet_Self *self, char *serverName, UINT32 serverNameLength, UINT32 serverPort );
BOOLEAN Hal_EthernetGetIncomingPacket( HAL_Ethernet_Self *self, UINT8 *incPacket, UINT32 maxLength );
void HAL_Ethernet_OpenUDPPort( HAL_Ethernet_Self *self );
void Hal_Ethernet_SendThenReceivePacket( HAL_Ethernet_Self *self, UINT8 *outPacket, UINT32 packetSize, HAL_Ethernet_TxCompletedCallback txCompletedCallback, void *delegate );
void HAL_Ethernet_CloseUDPPort( struct HAL_Ethernet_Self *self );

#endif //HAL_ETHERNET_H