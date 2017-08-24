
#ifndef __LIB_ETHERNET_H__
#define __LIB_ETHERNET_H__

#include "typedefs.h"

typedef struct Lib_Ethernet_Self Lib_Ethernet_Self;

void Lib_Ethernet_StartSendingProcess( Lib_Ethernet_Self *self );
void Lib_Ethernet_StopSendingProcess( Lib_Ethernet_Self *self );

#endif // __LIB_ETHERNET_H__
