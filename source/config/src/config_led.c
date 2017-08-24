/*
    this configuration file will setup the LEDs for the project
    GPIO pin setup is encapsulated here
*/

#include "../../functional/lib/lib_led/src/lib_led_p.h"
#include "../../functional/hal/hal_gpio.h"
#include "hal/src/hal_gpio_p.h"

STATIC BOOLEAN s_ledLoaded = FALSE;
//setup the gpio pins for this hypothetical platform
const HAL_GPIO_Line CONFIG_LED_LINE_WHITE = { HAL_GPIO_Port_C, HAL_GPIO_Pin_5 };
const HAL_GPIO_Line CONFIG_LED_LINE_RED = { HAL_GPIO_Port_C, HAL_GPIO_Pin_4 };

STATIC HAL_GPIO_Self whiteLEDGpio;
STATIC Lib_LED_Self whiteLED;

STATIC HAL_GPIO_Self redLEDGpio;
STATIC Lib_LED_Self redLED;

STATIC void Config_LED_Init( void )
{
    //setup white LED
    HAL_GPIO_CreateSelf( &whiteLEDGpio, &CONFIG_LED_LINE_WHITE);
    Lib_LED_CreateSelf( &whiteLED, &whiteLEDGpio );
    //setup red LED
    HAL_GPIO_CreateSelf( &redLEDGpio, &CONFIG_LED_LINE_RED );
    Lib_LED_CreateSelf( &redLED, &redLEDGpio );
}
Lib_LED_Self *Config_LED_GetRedLEDSelf()
{
    if( s_ledLoaded != TRUE )
    {
        s_ledLoaded = TRUE;
        Config_LED_Init();
    }
    return &redLED;
}

Lib_LED_Self *Config_LED_GetWhiteLEDSelf()
{
    if( s_ledLoaded != TRUE )
    {
        s_ledLoaded = TRUE;
        Config_LED_Init();
    }
    return &whiteLED;

}