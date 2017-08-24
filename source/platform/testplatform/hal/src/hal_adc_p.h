#ifndef LIB_ADC_P_H
#define LIB_ADC_P_H


struct HAL_ADC_Self
{
    int placeHlder;
};

void HAL_ADC_CreateSelf( struct HAL_ADC_Self *self );
#endif //LIB_ADC_P_H
