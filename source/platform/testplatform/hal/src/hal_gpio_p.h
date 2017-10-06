/*
    private header for the hal_gpio class
    contains the self definition
*/

#ifndef HAL_GPIO_P_H
#define HAL_GPIO_P_H

#include "typedefs.h"

/*ports on an undefined platform*/
typedef enum
{
    HAL_GPIO_Port_A,
    HAL_GPIO_Port_B,
    HAL_GPIO_Port_C,
    HAL_GPIO_Port_D,
    HAL_GPIO_Port_E,
    HAL_GPIO_Port_F,
    HAL_GPIO_Port_G,
    HAL_GPIO_Port_H,
    HAL_GPIO_PORT_COUNT
} HAL_GPIO_Port;
/* pins on an undefined test platform*/
typedef enum
{
    HAL_GPIO_Pin_0,
    HAL_GPIO_Pin_1,
    HAL_GPIO_Pin_2,
    HAL_GPIO_Pin_3,
    HAL_GPIO_Pin_4,
    HAL_GPIO_Pin_5,
    HAL_GPIO_Pin_6,
    HAL_GPIO_Pin_7,
    HAL_GPIO_Pin_8,
    HAL_GPIO_Pin_9,
    HAL_GPIO_Pin_10,
    HAL_GPIO_Pin_11,
    HAL_GPIO_Pin_12,
    HAL_GPIO_Pin_13,
    HAL_GPIO_Pin_14,
    HAL_GPIO_Pin_15,
    HAL_GPIO_PIN_COUNT
} HAL_GPIO_Pin;

typedef struct
{
    HAL_GPIO_Port port;
    HAL_GPIO_Pin pin;
} HAL_GPIO_Line;


struct HAL_GPIO_Self
{
    HAL_GPIO_Line *line;
    BOOLEAN lineState;
};


#endif //HAL_GPIO_P_H