#include "hal_gpio_p.h"

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
    BOOLEAN lineState = !self->lineState;

    /* this should call the appropriate GPIO function for the platform and get the state if the GPIO*/
    /* this is now setup to simply toggle the current state instance variable */

    return lineState;
}

void HAL_GPIO_ConfigureSelfAsSimpleIO( struct HAL_GPIO_Self *self, UINT8 startingState )
{
    //should configure the gpio pin as a simple IO
    //this is platform dependent
}

void HAL_GPIO_SetLineInterruptTrigger( struct HAL_GPIO_Self *self, InterruptEvent interruptEvent, void *interruptData, UINT8 trigger )
{
    //this should setup the gpio pins to trigger an interrupt and call the callback 'interruptEvent' when the gpio triggers on the specified edge


}

void HAL_GPIO_SetLine( struct HAL_GPIO_Self *self, BOOLEAN setValue )
{
    /* use the platform gpio interface to set the value of an output GPIO to 'setValue'*/
}