#ifndef LIB_ADC_P_H
#define LIB_ADC_P_H

#include "typedefs.h"

struct HAL_ADC_Self
{
    UINT32 adcValue;
    SINT32 direction;
};

void HAL_ADC_CreateSelf( struct HAL_ADC_Self *self );
#endif //LIB_ADC_P_H
