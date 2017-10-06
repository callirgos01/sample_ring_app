/*
    this configuration file deals with all things Buttons
    initializing the correct gpio, and passing it to the button class
    hooking up the hardware interrupt to the app
    initializing the self entity for the button
*/
#include "typedefs.h"
#include "lib_button/src/lib_button_config.h"
#include "hal/hal_gpio.h"
#include "hal/src/hal_gpio_p.h"

STATIC BOOLEAN s_configButtonLoaded = FALSE;

STATIC Lib_Button_Self s_buttonSelf;
STATIC HAL_GPIO_Self s_gpioSelf;

//setup a gpio pin where we get the input from the button
HAL_GPIO_Line CONFIG_BUTTON_LINE = { HAL_GPIO_Port_A, HAL_GPIO_Pin_0 };
STATIC void Config_Button_Init( )
{
    HAL_GPIO_CreateSelf( &s_gpioSelf, &CONFIG_BUTTON_LINE );
    //setting up the intial gpio state to digital input, since this is the line we are going to be setting up as an interrupt
    //so we can get the button interrupt
    HAL_GPIO_ConfigureSelfAsSimpleIO( &s_gpioSelf, HAL_GPIO_IOState_DigitalInputNoInternalPull );
    
    Lib_Button_CreateSelf( &s_buttonSelf, &s_gpioSelf );

}
Lib_Button_Self *Config_Button_GetButtonSelf( )
{
    if( s_configButtonLoaded != TRUE )
    {
        s_configButtonLoaded = TRUE;
        Config_Button_Init();
    }
    return &s_buttonSelf;

}