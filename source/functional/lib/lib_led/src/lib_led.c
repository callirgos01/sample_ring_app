
#include <stdio.h>
#include "typedefs.h"
#include "lib_led_p.h"
#include "../../functional/hal/hal_gpio.h"
#include "os/os_eventqueue.h"
#include "os/os_alarm.h"

void Lib_LED_CreateSelf( Lib_LED_Self *self, HAL_GPIO_Self *gpioLED )
{
    if ( self != NULL )
    {
        self->gpioLED = gpioLED;
        //I'm going to assume the LED is active high in this setting
        self->activeHigh = TRUE;
        self->miliSecondsOffTime = 0;
        self->miliSecondsOnTime = 0;
        self->ledState = FALSE;
    }
}

void Lib_LED_TurnLEDOn( Lib_LED_Self *self )
{
    /* use GPIO interface to turn on the LED */
    if ( self != NULL )
    {
        self->ledState = TRUE;//we can alternitevly get the state through the readgpio pin function
        HAL_GPIO_SetLine( self->gpioLED, self->activeHigh );
    }

}

void Lib_LED_TurnLEDOff( Lib_LED_Self *self )
{
    /* use GPIO interface to turn off the LED */
    if ( self != NULL )
    {
        self->ledState = FALSE;//we can alternitevly get the state through the readgpio pin function
        HAL_GPIO_SetLine( self->gpioLED, !self->activeHigh );
    }
}

STATIC void Lib_LED_StartPatternProcess( Lib_LED_Self *self )
{    
    if ( self != NULL )
    {
        //if the LED is currently on
        if( self->ledState == TRUE )
        {
            //turn it off
            Lib_LED_TurnLEDOff( self );
            //set an alarm to fire (off time miliseconds later)
            //alarm_set( Lib_LED_StartPatternProcess, self, self->miliSecondsOffTime );
            OS_Alarm_Set( (Event)Lib_LED_StartPatternProcess, self, OS_ALARM_MILISECONDS_TO_BEATS( self->miliSecondsOffTime ) );
        }
        else
        {
            //turn it on
            Lib_LED_TurnLEDOn( self );
            //set an alarm to fire (on time miliseconds later)
            //alarm_set( Lib_LED_StartPatternProcess, self, self->miliSecondsOnTime );
            OS_Alarm_Set( (Event)Lib_LED_StartPatternProcess, self, OS_ALARM_MILISECONDS_TO_BEATS( self->miliSecondsOnTime ) );
        }
    }
}

void Lib_LED_StartPattern( Lib_LED_Self *self, UINT32 miliSecondsOnTime, UINT32 miliSecondsOffTime )
{
    /* 
        use an alarm system to turn on / off the led in a specific pattern, with a specific on time, and off time.
    */
    if ( self != NULL )
    {
        self->miliSecondsOffTime = miliSecondsOffTime;
        self->miliSecondsOnTime = miliSecondsOnTime;
        OS_Alarm_Cancel( (Event)Lib_LED_StartPatternProcess, self );
        //QUEUE UP THE PATTERN EVENT TO TRIGGER SYNCHRONOUSLY ( Lib_LED_StartPatternProcess, self);
        OS_EventQueue_Queue( (Event) Lib_LED_StartPatternProcess, self);
    }
}

void Lib_LED_StopPattern( Lib_LED_Self *self )
{
    if( self != NULL )
    {
        /*cancels the alarms (if any) from firing*/    
        //ALARM_CANCEL 
        OS_Alarm_Cancel( (Event)Lib_LED_StartPatternProcess, self );
        //alarm_cancel( Lib_LED_StartPatternProcess );    
        /*and turns off the LED if its on */
        Lib_LED_TurnLEDOff( self );
    }

}

