/* 
    private header for the button identity
*/
#ifndef LIB_BUTTON_P_H
#define LIB_BUTTON_P_H

#include "../lib_button.h"
#include "../../functional/hal/hal_gpio.h"

struct Lib_Button_Self
{
    void *delegate;
    HAL_GPIO_Self *buttonInterrupt;
    Lib_Button_ButtonPressEvent buttonPressCallBack;
    Lib_Button_ButtonReleasedEvent buttonReleasedCallback;
};

#endif //LIB_BUTTON_P_H