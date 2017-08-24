
#ifndef __LIB_BATTERY_P_H__
#define __LIB_BATTERY_P_H__

#include "typedefs.h"
#include "../lib_battery.h"
#include "../../functional/hal/hal_adc.h"

struct Lib_Battery_Self
{
    UINT32 lowBatteryThreshold;
    HAL_ADC_Self *halADCSelf;
    void *delegate;
    Lib_Battery_LowBatteryCallback lowBatteryCallback;
    Lib_Battery_ChargerConnectedCallback chargerConnectedCallback;
};

void Lib_Battery_CreateSelf( Lib_Battery_Self *self, HAL_ADC_Self *halADCSelf, UINT32 lowBatteryThreshold );

#endif // __LIB_BATTERY_P_H__
