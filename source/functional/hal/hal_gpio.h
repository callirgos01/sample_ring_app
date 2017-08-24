#ifndef HAL_GPIO_H
#define HAL_GPIO_H

typedef struct HAL_GPIO_Self HAL_GPIO_Self;
/*rIO States for a typical io pin*/

typedef UINT8 HAL_GPIO_IOState;
enum
{
    HAL_GPIO_IOState_DoNotConfigure,
    HAL_GPIO_IOState_DigitalOutputLowPushPullNoInternalPull,
    HAL_GPIO_IOState_DigitalOutputHighPushPullNoInternalPull,
    HAL_GPIO_IOState_DigitalOutputLowOpenDrainNoInternalPull,
    HAL_GPIO_IOState_DigitalOutputLowOpenDrainInternalPullDown,
    HAL_GPIO_IOState_DigitalOutputLowOpenDrainInternalPullUp,
    HAL_GPIO_IOState_DigitalOutputHighImpedanceOpenDrainNoInternalPull,
    HAL_GPIO_IOState_DigitalOutputHighImpedanceOpenDrainInternalPullDown,
    HAL_GPIO_IOState_DigitalOutputHighImpedanceOpenDrainInternalPullUp,
    HAL_GPIO_IOState_DigitalInputNoInternalPull,
    HAL_GPIO_IOState_DigitalInputInternalPullDown,
    HAL_GPIO_IOState_DigitalInputInternalPullUp,
    HAL_GPIO_IOState_AnalogInputNoInternalPull,
    HAL_GPIO_IOState_AnalogInputInternalPullDown,
    HAL_GPIO_IOState_AnalogInputInternalPullUp,
};

/* edge triggers for gpio pins */
typedef enum
{
    HAL_GPIO_InterruptTrigger_None,
    HAL_GPIO_InterruptTrigger_High,
    HAL_GPIO_InterruptTrigger_Low,
    HAL_GPIO_InterruptTrigger_Edge
} HAL_GPIO_InterruptTrigger;

BOOLEAN HAL_GPIO_ReadLine( HAL_GPIO_Self *self );
void HAL_GPIO_ConfigureSelfAsSimpleIO( HAL_GPIO_Self *self, HAL_GPIO_IOState startingState );
void HAL_GPIO_SetLineInterruptTrigger( HAL_GPIO_Self *self, InterruptEvent interruptEvent, void *interruptData, HAL_GPIO_InterruptTrigger trigger );
void HAL_GPIO_SetLine( HAL_GPIO_Self *self, BOOLEAN setValue );

#endif //HAL_GPIO_H