
#include "typedefs.h"
#include "lib_battery_p.h"
#include "../../functional/hal/hal_adc.h"
#include "../../lib_charger/lib_charger.h"

STATIC void Lib_Battery_ChargerConnected( Lib_Battery_Self *self )
{
    if ( self != NULL )
    {
        //stop reading the battery levels
        //trigger the event to the upper layers.
        //alarm_cancel( Lib_Battery_StartPeriodicBatteryChecks, self );
        if( self->chargerConnectedCallback != NULL )
        {
            self->chargerConnectedCallback( self->delegate );
        }
    }
}

STATIC void Lib_Battery_ChargerDiscConnected( Lib_Battery_Self *self )
{
    if ( self != NULL )
    {
        //continue the reading of the battery levels
        //trigger events if needed
        Lib_Battery_StartPeriodicBatteryChecks( self );
    }
}

void Lib_Battery_CreateSelf( Lib_Battery_Self *self, HAL_ADC_Self *halADCSelf, Lib_Charger_Self *charger, UINT32 lowBatteryThreshold )
{
    if ( self != NULL )
    {
        self->lowBatteryThreshold = lowBatteryThreshold;
        self->halADCSelf = halADCSelf;
        self->charger = charger;

        //setup the interrupts from the charger
        Lib_Charger_SetChargerConnectedCallback( self->charger, self, (Lib_Charger_ChargerConnectedEvent) Lib_Battery_ChargerConnected );
        Lib_Charger_SetChargerDisconnectedCallback( self->charger, self, (Lib_Charger_ChargerDisconnectedEvent) Lib_Battery_ChargerDiscConnected );

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
