/*
    this file should configure everything that has to do with the battery connection
    should setup the ADC and pass its object to the battery library to use
*/
#include "typedefs.h"

#include "lib_battery/src/lib_battery_config.h"
#include "../../functional/hal/hal_adc.h"
#include "hal/src/hal_adc_p.h"
#include "config_charger_p.h"

#define LOW_BATTERY_THRESHOLD 3500

STATIC BOOLEAN s_configBatteryLoaded = FALSE;

STATIC Lib_Battery_Self s_batterySelf;
STATIC HAL_ADC_Self s_halADCSelf;

STATIC void Config_Battery_Init( void )
{
    HAL_ADC_CreateSelf( &s_halADCSelf );
    
    Lib_Battery_CreateSelf( &s_batterySelf, &s_halADCSelf, Config_Charger_GetChargerSelf(), LOW_BATTERY_THRESHOLD );
}
Lib_Battery_Self *Config_Battery_GetBatterySelf( void )
{
    if( s_configBatteryLoaded != TRUE )
    {
        s_configBatteryLoaded = TRUE;
        Config_Battery_Init();
    }
    return &s_batterySelf;

}
