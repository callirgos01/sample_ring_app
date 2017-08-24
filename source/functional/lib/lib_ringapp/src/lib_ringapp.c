/*
    this app controls the main behavior of the ring app
    all peripherals are controlled / started/ stopped from here.
*/
#include <stdio.h>
#include "typedefs.h"
#include "lib_ringapp_p.h"
#include "../../lib_button/lib_button.h"
#include "../../lib_led/lib_led.h"
/*
    call back triggers when the button is pressed
*/
STATIC void Lib_RingApp_ButtonPressed( Lib_RingApp_Self *self )
{
    if( self != NULL )
    {
        //ask battery if we have enough battery
        //if we have enough battery
        {
            //tell the white led process to start blinking
            Lib_LED_TurnLEDOn( self->whiteLED );
            //tell the ethernet process to start sending stuff
            //
            Lib_Ethernet_StartSendingProcess( self->ethernet );
        }
        //else
        {
                //we should already be blinking the red light
        }
    }
}
/*
    call back ttriggers when the button is released
*/
STATIC void Lib_RingApp_ButtonReleased( Lib_RingApp_Self *self )
{
    if( self != NULL )
    {
        //stop white led
        Lib_LED_TurnLEDOff( self->whiteLED );
        //tell ethernet process to stop.
        Lib_Ethernet_StopSendingProcess( self->ethernet );
    }
}
/*Lib_Ethernet_Self *ethernet, Lib_LED_Self *redLED, Lib_LED_Self *whiteLED,
    Lib_Battery_Self *battery, Lib_Charger_Self *charger )*/
void Lib_RingApp_CreateSelf( Lib_RingApp_Self *self, Lib_Button_Self *button, Lib_Ethernet_Self *ethernet, Lib_LED_Self *redLED, Lib_LED_Self *whiteLED, void *battery, void *charger )
{
    if( self != NULL )
    {
        self->button = button;
        self->ethernet = ethernet;
        self->redLED = redLED;
        self->whiteLED = whiteLED;
        self->battery = battery;
        self->charger = charger;

        //setup the button hook ups that pertain to our operations
        Lib_Button_SetButtonPressedCallback( self->button, self, (Lib_Button_ButtonPressEvent) Lib_RingApp_ButtonPressed );
        Lib_Button_SetButtonReleasedCallback( self->button, self, (Lib_Button_ButtonReleasedEvent) Lib_RingApp_ButtonReleased );
    }
}

void Lib_RingApp_Start( Lib_RingApp_Self *self )
{
    //this should kick off all functionality
    //place holder code to confirm that we are all hooked up
    /*printf("self 0x%08X\r\n",self);
    printf("button 0x%08X\r\n",self->button);
    printf("ethernet 0x%08X\r\n",self->ethernet);
    printf("redLED 0x%08X\r\n",self->redLED);
    printf("whiteLED 0x%08X\r\n",self->whiteLED);
    printf("battery 0x%08X\r\n",self->battery);
    printf("charger 0x%08X\r\n",self->charger);*/
    printf("happiness\r\n");
        
}