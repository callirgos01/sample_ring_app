
#include "typedefs.h"
#include <stdio.h>
#include "lib_battery_p.h"
#include "os/os_alarm.h"
#include "../../functional/hal/hal_adc.h"
#include "../../lib_charger/lib_charger.h"
STATIC void Lib_Battery_CheckBattery( Lib_Battery_Self *self );


STATIC void Lib_Battery_ChargerConnected( Lib_Battery_Self *self )
{
    if ( self != NULL )
    {
        //stop reading the battery levels
        OS_Alarm_Cancel( (Event)Lib_Battery_CheckBattery, self );
        //trigger the event to the upper layers.
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
        DPrintf("CHARGER DISCONNECTED\r\n");
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

STATIC void Lib_Battery_CheckBattery( Lib_Battery_Self *self )
{
    if ( self != NULL )
    {
        UINT32 batteryValue = 0;
        if( Hal_ADC_ReadADCValue( self->halADCSelf, &batteryValue) )
        {
            DPrintf( "Battery Level %u mV\r\n", batteryValue );
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

    OS_Alarm_Cancel( (Event)Lib_Battery_CheckBattery, self );
    //setup a timer/alarm that will check battery every minute
    //if battery is below the set threshold
    //this library will notify a client defined call back to propagate behavior
    OS_Alarm_Repeat( (Event)Lib_Battery_CheckBattery, self, 0, LIB_BATTERY_READ_INTERVAL, OS_ALARM_REPEAT_FOREVER );
}
