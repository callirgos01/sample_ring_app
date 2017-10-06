/*
This file takes care of the business logic associated with the button.
like what to do when the button is pressed.
And how to propate that event
*/
#include <stdio.h>
#include "typedefs.h"
#include "hal/hal_gpio.h"
#include "lib_button_p.h"

STATIC void Lib_Button_ProcessInterrupt ( Lib_Button_Self *self )
{   
    /*add some debouncing if needed*/
    if( self != NULL )
    {
        //I'm going to assume that the line being high means the button is being pressed.
        //  this line being low means the button is not being pressed.
        // this even should trigger on every edge transition
        //so I gotta figure out which transition it is and dispath the appropriate callback
        BOOLEAN buttonState = HAL_GPIO_ReadLine( self->buttonInterrupt );
        if( buttonState )
        {
            if( self->buttonPressCallBack != NULL )
            {
                self->buttonPressCallBack( self->delegate );
            }            
        }
        else
        {
            if( self->buttonReleasedCallback != NULL )
            {
                self->buttonReleasedCallback( self->delegate );
            }            
        }
    }

}
STATIC /*volatile*/ void Lib_Button_OnButtonTrigger( /*volatile*/ Lib_Button_Self *self )
{
    /* THIS IS IN AN INTERRUPT CONTEXT */
    /* ON A REAL SYSTEM I WOULD USE WHATEVER OS QUEUE WE ARE CURRENTLY USING TO QUEUE UP A SYNCHRONOUS EVENT */
    /* BECAUSE OF THE LACK OF SUCH SYSTEM IN THIS SAMPLE PLATFORM, I'M GOING TO BE MAKING DIRECT CALLS TO THE REQUIRED STATUS AND CALLBACKS */
    // I WOULD DO THIS 
    // QUEUE( Lib_Button_ProcessInterrupt, self );
    Lib_Button_ProcessInterrupt( self );
}

void Lib_Button_CreateSelf( Lib_Button_Self *self, HAL_GPIO_Self *buttonInterrupt )
{
    if( self != NULL )
    {
        //intialize self with all  0s using memset when available.
        self->buttonInterrupt = buttonInterrupt;
        //have the GPIO layer setup an interrupt to trigger on both low and high.
        //hook up the interrupt to a callback
        HAL_GPIO_SetLineInterruptTrigger( self->buttonInterrupt, ( InterruptEvent ) Lib_Button_OnButtonTrigger, (void *) self, HAL_GPIO_InterruptTrigger_Edge );
    }    
}


void Lib_Button_SetButtonPressedCallback( Lib_Button_Self *self, void *delegate, Lib_Button_ButtonPressEvent buttonPressedCallback )
{
    if( self != NULL )
    {
        self->delegate = delegate;
        self->buttonPressCallBack = buttonPressedCallback; 
    }
}

void Lib_Button_SetButtonReleasedCallback( Lib_Button_Self *self, void *delegate, Lib_Button_ButtonReleasedEvent buttonReleasedCallback )
{
    if( self != NULL )
    {
        self->delegate = delegate;
        self->buttonReleasedCallback = buttonReleasedCallback;
    }

}


