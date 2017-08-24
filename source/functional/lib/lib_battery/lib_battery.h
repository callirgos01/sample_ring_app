
#ifndef __LIB_BATTERY_H__
#define __LIB_BATTERY_H__

#include "typedefs.h"
typedef void (*Lib_Battery_LowBatteryCallback)( void* );
typedef void (*Lib_Battery_ChargerConnectedCallback)( void* );
typedef struct Lib_Battery_Self Lib_Battery_Self;

void Lib_Battery_StartPeriodicBatteryChecks( Lib_Battery_Self *self );
void Lib_Battery_SetLowBatteryCallback( Lib_Battery_Self *self, Lib_Battery_LowBatteryCallback lowBatteryCallback, void* delegate );
void Lib_Battery_SetChargerConnectedCallback( Lib_Battery_Self *self, Lib_Battery_ChargerConnectedCallback chargerConnectedCallback, void* delegate );

#endif // __LIB_BATTERY_H__
