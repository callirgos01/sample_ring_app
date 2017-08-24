/*
    attempt at a private header in C, to obfuscate the private values of the self object
*/
#ifndef LIB_RINGAPP_P_H
#define LIB_RINGAPP_P_H

#include "../lib_ringapp.h"
#include "../../lib_button/lib_button.h"
#include "../../lib_led/lib_led.h"
#include "../../lib_ethernet/lib_ethernet.h"
#include "../../lib_battery/lib_battery.h"
#include "../../lib_charger/lib_charger.h"

struct Lib_RingApp_Self
{
    Lib_Button_Self *button;
    Lib_Ethernet_Self * ethernet; //Lib_Ethernet_Self *ethernet; 
    Lib_LED_Self *redLED;
    Lib_LED_Self *whiteLED; //Lib_LED_Self *whiteLED;
    Lib_Battery_Self *battery; //Lib_Battery_Self *battery;
    void *charger; //Lib_Charger_Self *charger;
    BOOLEAN lowBattery;
};

//void Lib_RingApp_CreateSelf( Lib_RingApp_Self *self, Lib_Button_Self *button, Lib_Ethernet_Self *ethernet, Lib_LED_Self *redLED, Lib_LED_Self *whiteLED,
//                            Lib_Battery_Self *battery, Lib_Charger_Self *charger );
void Lib_RingApp_CreateSelf( Lib_RingApp_Self *self, Lib_Button_Self *button, Lib_Ethernet_Self *ethernet, Lib_LED_Self *redLED, Lib_LED_Self *whiteLED, Lib_Battery_Self *battery );

#endif //LIB_RINGAPP_P_H