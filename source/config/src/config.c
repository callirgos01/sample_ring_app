/*
this file is the entry point of the project
this file will setup all the handles for all the components in the system and link them together
it uses lazy initializations to get all the information needed to build the project
*/
#include "typedefs.h"
#include "../../functional/lib/lib_ringapp/src/lib_ringapp_p.h"

#include "config_button_p.h"
//#include "config_ethernet_p.h"
#include "config_led_p.h"
//#include "config_battery_p.h"
//#include "config_charger_p.h"


STATIC BOOLEAN s_configAppLoaded = FALSE;
//static declaration of the self objects
STATIC Lib_RingApp_Self s_ringAppSelf;

/*
    this function creates the app main self, with all the other entities needed.
*/
STATIC Lib_RingApp_Self *Config_GetRingAppSelf( void )
{
    //lazy initialization used here.
    // only initialize modules if they are required
    if( s_configAppLoaded != TRUE )
    {
        s_configAppLoaded = TRUE;
        //per the specs the ring sample app will have the following peripherals
        //this creates an instance of each of the peripherals specified
        /*
            a.) 1 spring-loaded button that may be pushed and held by a user.
            b.) 1 Ethernet interface. Assume that the driver is functional, and the device has a valid IP address and is Internet-accessible. BSD sockets are available to use in the application.
            c.) 1 white LED, controllable by GPIO.
            d.) 1 red LED, controllable by GPIO.
            e.) 1 Battery monitor, read via ADC. Units read are in units of millivolts.
            f.) 1 USB battery charger interface, which may be plugged and unplugged at any time to charge or discharge the battery. Assume that all battery charging functionality is independent and properly working.
        */
        Lib_RingApp_CreateSelf( &s_ringAppSelf,
                                Config_Button_GetButtonSelf(),
                                NULL, //Config_Ethernet_GetEthernetSelf(),
                                Config_LED_GetRedLEDSelf(),
                                Config_LED_GetWhiteLEDSelf(),
                                NULL, //Config_Battery_GetBatterySelf(),
                                NULL //Config_Charger_GetChargerSelf()
                                );
    }
    //this returns a pointer to the statically allocated self.
    return &s_ringAppSelf;
}
/*
    this function calls the app start function and passes the information needed to perform its tasks
*/
void Config_AppStartApp( void )
{
    Lib_RingApp_Start( Config_GetRingAppSelf( ) );    
}