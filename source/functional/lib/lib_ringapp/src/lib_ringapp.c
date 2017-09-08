/*
    this app controls the main behavior of the ring app
    all peripherals are controlled / started/ stopped from here.
*/
#include <stdio.h>
#include "typedefs.h"
#include "lib_ringapp_p.h"
#include "../../lib_button/lib_button.h"
#include "../../lib_led/lib_led.h"
#include "os/os_eventqueue.h"
/*
    call back triggers when the button is pressed
*/
STATIC void Lib_RingApp_ButtonPressed( Lib_RingApp_Self *self )
{
    if( self != NULL )
    {
        //ask battery if we have enough battery
        //if we have enough battery
        if( self->lowBattery != TRUE )
        {
            //tell the white led process to start blinking
            Lib_LED_TurnLEDOn( self->whiteLED );
            //tell the ethernet process to start sending stuff
            Lib_Ethernet_StartSendingProcess( self->ethernet );
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
STATIC void Lib_RingApp_ChargerConnected( Lib_RingApp_Self *self ) 
{
    //this wasnt part of the specifications but if the charger is connected we will resume normal operations.
    self->lowBattery = FALSE;
    //we might want to check the current state of the button press, and start transmitting if the charger was connected by the button was being pressed.
    //otherwise the next time the button is pressed it will check if the low batter boolean is true, an then turn on the transmissions as needed.
}
STATIC void Lib_RingApp_LowBattery( Lib_RingApp_Self *self ) 
{
    //this is called when the batter is below the low battery threshold
    //  a.) While the battery voltage is <3.5V, the system shall be put in a non-functional state, meaning the white LED shall not illuminate and the Network Application shall not be executed, even if the button is pushed.
   //   b.) While the battery voltage is <3.5V, the red LED shall blink at a rate of 2Hz with a 25% duty cycle.
   //   c.) If the battery voltage returns to an operable level (>= 3.5V), the red LED shall stop blinking and operation shall resume as normal.
    //2Hz = twise a second. So every 500ms, out of those 500ms, 25% = on time, and 75% is offtime. 125ms on time and 375ms offtime.
    UINT32 onTime = 125;
    UINT32 offTime = 375;

    self->lowBattery = TRUE;
    //turn off White LED if Its on
    //stop communication if its running
    Lib_LED_TurnLEDOff( self->whiteLED );
    Lib_Ethernet_StopSendingProcess( self->ethernet );
    
    Lib_LED_StartPattern( self->redLED, onTime, offTime );
}
/*Lib_Ethernet_Self *ethernet, Lib_LED_Self *redLED, Lib_LED_Self *whiteLED,
    Lib_Battery_Self *battery, Lib_Charger_Self *charger )*/
void Lib_RingApp_CreateSelf( Lib_RingApp_Self *self, Lib_Button_Self *button, Lib_Ethernet_Self *ethernet, Lib_LED_Self *redLED, Lib_LED_Self *whiteLED, Lib_Battery_Self *battery )
{
    if( self != NULL )
    {
        self->button = button;
        self->ethernet = ethernet;
        self->redLED = redLED;
        self->whiteLED = whiteLED;
        self->battery = battery;
        self->lowBattery = FALSE;
        //setup the button hook ups that pertain to our operations
        Lib_Button_SetButtonPressedCallback( self->button, self, (Lib_Button_ButtonPressEvent) Lib_RingApp_ButtonPressed );
        Lib_Button_SetButtonReleasedCallback( self->button, self, (Lib_Button_ButtonReleasedEvent) Lib_RingApp_ButtonReleased );
        //setup the battery handler
        Lib_Battery_SetLowBatteryCallback( self->battery, (Lib_Battery_LowBatteryCallback) Lib_RingApp_LowBattery, self );
        Lib_Battery_SetChargerConnectedCallback( self->battery, (Lib_Battery_ChargerConnectedCallback) Lib_RingApp_ChargerConnected, self );
    }
}

void Lib_RingApp_Start( Lib_RingApp_Self *self )
{
    printf("WORKS!\r\n");

    Lib_Battery_StartPeriodicBatteryChecks( self->battery );        
}