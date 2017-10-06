
#ifndef HAL_ETHERNET_P_H
#define HAL_ETHERNET_P_H

#define MAX_SERVER_NAME_SIZE 200
#define PACKET_SIZE 2
struct HAL_Ethernet_Self
{
    char serverName[MAX_SERVER_NAME_SIZE];
    UINT32 serverPort;

    UINT8 incomingPacket[PACKET_SIZE];

    void ( *txCompletedCallback )( void *delegate);
    void *delegate;
};


#endif //HAL_ETHERNET_P_H