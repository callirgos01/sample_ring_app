
#ifndef __LIB_LED_P_H__
#define __LIB_LED_P_H__

#include "typedefs.h"
#include "../lib_led.h"
#include "../../functional/hal/hal_gpio.h"

struct Lib_LED_Self
{
    HAL_GPIO_Self *gpioLED;
    BOOLEAN activeHigh;
    UINT32 miliSecondsOnTime;
    UINT32 miliSecondsOffTime;
    BOOLEAN ledState;
};

void Lib_LED_CreateSelf( Lib_LED_Self *self, HAL_GPIO_Self *gpioLED );

#endif // __LIB_LED_P_H__
