
#include "typedefs.h"
#include "lib_battery_p.h"
#include "../../functional/hal/hal_adc.h"

void Lib_Battery_CreateSelf( Lib_Battery_Self *self, HAL_ADC_Self *halADCSelf, UINT32 lowBatteryThreshold )
{
    if ( self != NULL )
    {
        self->lowBatteryThreshold = lowBatteryThreshold;
        self->halADCSelf = halADCSelf;
    }
}

void Lib_Battery_SetLowBatteryCallback( Lib_Battery_Self *self, Lib_Battery_LowBatteryCallback lowBatteryCallback, void* delegate )
{
    if ( self != NULL )
    {
        self->lowBatteryCallback = lowBatteryCallback;
        self->delegate = delegate;
    }
}

void Lib_Battery_SetChargerConnectedCallback( Lib_Battery_Self *self, Lib_Battery_ChargerConnectedCallback chargerConnectedCallback, void* delegate )
{
    if ( self != NULL )
    {
        self->chargerConnectedCallback = chargerConnectedCallback;
        self->delegate = delegate;
    }
}

void Lib_Battery_CheckBattery( Lib_Battery_Self *self )
{   
    if ( self != NULL )
    {
        UINT32 batteryValue = 0;
        if( Hal_ADC_ReadADCValue( self->halADCSelf, &batteryValue) )
        {
            //read value successfully
            //test is against the threshold
            if( batteryValue <= self->lowBatteryThreshold )
            {
                if( self->lowBatteryCallback != NULL )
                {
                    self->lowBatteryCallback( self->delegate );
                }
            }
        }
    }
}
void Lib_Battery_StartPeriodicBatteryChecks( Lib_Battery_Self *self )
{
    //setup a timer/alarm that will check battery every minute
    //if battery is below the set threshold
    //this library will notify a client defined call back to propagate behavior

    //alarm_set_repeat( Lib_Battery_CheckBattery, 60000. self);
}
