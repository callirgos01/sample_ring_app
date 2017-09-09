
#include <stdio.h>
#include "typedefs.h"
#include "hal_gpio_p.h"
#include "os/os_alarm.h"

void HAL_GPIO_CreateSelf( struct HAL_GPIO_Self *self, HAL_GPIO_Line *line )
{
    self->line = line;
    
    //initializing a dummy line state instance variable
    self->lineState = FALSE;
    /*
        this would setup the hal layer to use this gpio pin
    */
}

BOOLEAN HAL_GPIO_ReadLine( struct HAL_GPIO_Self *self, HAL_GPIO_Line *line )
{
    BOOLEAN lineState = self->lineState;
    
    self->lineState = !self->lineState;
    /* this should call the appropriate GPIO function for the platform and get the state if the GPIO*/
    /* this is now setup to simply toggle the current state instance variable */

    return lineState;
}

void HAL_GPIO_ConfigureSelfAsSimpleIO( struct HAL_GPIO_Self *self, UINT8 startingState )
{
    //should configure the gpio pin as a simple IO
    //this is platform dependent
}
//initialize a static array of times, so we can cycle through the, and give different interval times.
//to different events.
//the time is not realted to the event, they will be randomly asigned, so we may simulate asynchronous events at different times
#define MAX_TIMES ( 5 )
static UINT8 s_timesIndex = 0;
STATIC UINT32 s_test_times[MAX_TIMES] = {
    60,
    120,
    55,
    22,
    300
};
void HAL_GPIO_SetLineInterruptTrigger( struct HAL_GPIO_Self *self, InterruptEvent interruptEvent, void *interruptData, UINT8 trigger )
{
    //this should setup the gpio pins to trigger an interrupt and call the callback 'interruptEvent' when the gpio triggers on the specified edge
    //lets simulate some events from this stubbed driver
    //setup an alarm to trigger a a constant interval.
    UINT32 beatsToWait = OS_ALARM_SECONDS_TO_BEATS( s_test_times[s_timesIndex++] );

    OS_Alarm_Repeat( (Event) interruptEvent, interruptData, beatsToWait, beatsToWait, OS_ALARM_REPEAT_FOREVER );

}

void HAL_GPIO_SetLine( struct HAL_GPIO_Self *self, BOOLEAN setValue )
{
    /* use the platform gpio interface to set the value of an output GPIO to 'setValue'*/
    DPrintf("GPIO{ port = %u, pin = %u } = %s\r\n", self->line->port, self->line->pin, (setValue) ? "On": "Off");
    
}