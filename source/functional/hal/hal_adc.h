#ifndef LIB_ADC_H
#define LIB_ADC_H

typedef struct HAL_ADC_Self HAL_ADC_Self;

BOOLEAN Hal_ADC_ReadADCValue( HAL_ADC_Self *self, UINT32 *adcValue );

#endif //LIB_ADC_H

