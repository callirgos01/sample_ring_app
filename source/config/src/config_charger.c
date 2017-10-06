/*
    this configuration file deals with all things Charger
    initializing the correct gpio, and passing it to the charger class
    hooking up the hardware interrupt to the app
    initializing the self entity for the charger
*/
#include "typedefs.h"
#include "../../functional/lib/lib_charger/src/lib_charger_p.h"
#include "../../functional/hal/hal_gpio.h"
#include "hal/src/hal_gpio_p.h"

STATIC BOOLEAN s_configChargerLoaded = FALSE;

STATIC Lib_Charger_Self s_chargerSelf;
STATIC HAL_GPIO_Self s_gpioSelf;

//setup a gpio pin where we get the input from the charger
HAL_GPIO_Line CONFIG_CHARGER_CONNECTED_INTERRUPT_PIN = { HAL_GPIO_Port_B, HAL_GPIO_Pin_4 };
STATIC void Config_Charger_Init( )
{
    HAL_GPIO_CreateSelf( &s_gpioSelf, &CONFIG_CHARGER_CONNECTED_INTERRUPT_PIN );
    HAL_GPIO_ConfigureSelfAsSimpleIO( &s_gpioSelf, HAL_GPIO_IOState_DigitalInputNoInternalPull );
    
    Lib_Charger_CreateSelf( &s_chargerSelf, &s_gpioSelf );

}

Lib_Charger_Self *Config_Charger_GetChargerSelf( void )
{
    if( s_configChargerLoaded != TRUE )
    {
        s_configChargerLoaded = TRUE;
        Config_Charger_Init();
    }
    return &s_chargerSelf;

}