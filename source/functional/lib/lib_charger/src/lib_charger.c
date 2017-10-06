
#include <stdio.h>
#include "typedefs.h"
#include "hal/hal_gpio.h"
#include "lib_charger_p.h"
#include "os/os_eventqueue.h"
#include "os/os_alarm.h"

STATIC void Lib_Charger_ProcessInterrupt ( Lib_Charger_Self *self )
{   
    /*add some debouncing if needed*/
    if( self != NULL )
    {       
        BOOLEAN chargerPresentState = HAL_GPIO_ReadLine( self->chargerConnectedInterrupt );
        if( chargerPresentState )
        {
            if( self->chargerConnected != NULL )
            {
                self->chargerConnected( self->delegate );
            }            
        }
        else
        {
            if( self->chargerDisconnected != NULL )
            {
                self->chargerDisconnected( self->delegate );
            }            
        }
    }

}

STATIC /*volatile*/ void Lib_Charger_OnChargerConnectedTrigger( /*volatile*/ Lib_Charger_Self *self )
{
    /* THIS IS IN AN INTERRUPT CONTEXT */
    /* ON A REAL SYSTEM I WOULD USE WHATEVER OS QUEUE WE ARE CURRENTLY USING TO QUEUE UP A SYNCHRONOUS EVENT */
    /* BECAUSE OF THE LACK OF SUCH SYSTEM IN THIS SAMPLE PLATFORM, I'M GOING TO BE MAKING DIRECT CALLS TO THE REQUIRED STATUS AND CALLBACKS */
    // I WOULD DO THIS INSTEAD
    OS_EventQueue_Queue( (Event) Lib_Charger_ProcessInterrupt, self );
    //Lib_Charger_ProcessInterrupt( self );
}

void Lib_Charger_CreateSelf( Lib_Charger_Self *self, HAL_GPIO_Self *chargerConnectedInterrupt )
{
    if( self != NULL )
    {
        self->chargerConnectedInterrupt = chargerConnectedInterrupt;
        HAL_GPIO_SetLineInterruptTrigger( self->chargerConnectedInterrupt, ( InterruptEvent ) Lib_Charger_OnChargerConnectedTrigger, (void *) self, HAL_GPIO_InterruptTrigger_Edge );
    }    
}


void Lib_Charger_SetChargerConnectedCallback( Lib_Charger_Self *self, void *delegate, Lib_Charger_ChargerConnectedEvent chargerConnectedCallback )
{
    if( self != NULL )
    {
        self->delegate = delegate;
        self->chargerConnected = chargerConnectedCallback; 
    }
}

void Lib_Charger_SetChargerDisconnectedCallback( Lib_Charger_Self *self, void *delegate, Lib_Charger_ChargerDisconnectedEvent chargerDisconnectedCallback )
{
    if( self != NULL )
    {
        self->delegate = delegate;
        self->chargerDisconnected = chargerDisconnectedCallback;
    }

}
