
#ifndef __LIB_BATTERY_P_H__
#define __LIB_BATTERY_P_H__

#include "typedefs.h"
#include "../lib_battery.h"
#include "../../lib_charger/lib_charger.h"
#include "../../functional/hal/hal_adc.h"
#define LIB_BATTERY_READ_INTERVAL_SECONDS ( 60 )
#define LIB_BATTERY_READ_INTERVAL ( OS_ALARM_SECONDS_TO_BEATS(LIB_BATTERY_READ_INTERVAL_SECONDS))
struct Lib_Battery_Self
{
    UINT32 lowBatteryThreshold;
    HAL_ADC_Self *halADCSelf;
    Lib_Charger_Self *charger;
    void *delegate;
    Lib_Battery_LowBatteryCallback lowBatteryCallback;
    Lib_Battery_ChargerConnectedCallback chargerConnectedCallback;
};

void Lib_Battery_CreateSelf( Lib_Battery_Self *self, HAL_ADC_Self *halADCSelf, Lib_Charger_Self *charger, UINT32 lowBatteryThreshold );

#endif // __LIB_BATTERY_P_H__
