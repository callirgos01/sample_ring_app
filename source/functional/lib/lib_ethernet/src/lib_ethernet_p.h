
#ifndef __LIB_ETHERNET_P_H__
#define __LIB_ETHERNET_P_H__

#include "typedefs.h"
#include "lib_ethernet/lib_ethernet.h"
#include "hal/hal_ethernet.h"


#define PACKET_SIZE 2

struct Lib_Ethernet_Self
{    
    UINT16 count;
    HAL_Ethernet_Self *halEthernet;
    UINT32 time;
    BOOLEAN running;
};

#endif // __LIB_ETHERNET_P_H__
