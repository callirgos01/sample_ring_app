#ifndef __LIB_BATTERY_CONFIG_H__
#define __LIB_BATTERY_CONFIG_H__

#include "lib_battery/src/lib_battery_p.h"

void Lib_Battery_CreateSelf( Lib_Battery_Self *self, HAL_ADC_Self *halADCSelf, Lib_Charger_Self *charger, UINT32 lowBatteryThreshold );

#endif //__LIB_BATTERY_CONFIG_H__