
#ifndef __LIB_CHARGER_H__
#define __LIB_CHARGER_H__

#include "typedefs.h"

typedef struct Lib_Charger_Self Lib_Charger_Self;

typedef void ( *Lib_Charger_ChargerConnectedEvent )( void* delegate );
typedef void ( *Lib_Charger_ChargerDisconnectedEvent )( void* delegate );

void Lib_Charger_SetChargerConnectedCallback( Lib_Charger_Self *self, void *delegate, Lib_Charger_ChargerConnectedEvent chargerConnectedCallback );
void Lib_Charger_SetChargerDisconnectedCallback( Lib_Charger_Self *self, void *delegate, Lib_Charger_ChargerDisconnectedEvent chargerDisconnectedCallback );


#endif // __LIB_CHARGER_H__
