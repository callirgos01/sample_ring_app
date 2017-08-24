#include "typedefs.h"
#include "hal_adc_p.h"
//#include <stdio.h>
//#include <string.h>

void HAL_ADC_CreateSelf( struct HAL_ADC_Self *self )
{
    /*initialize the ADC*/

}

BOOLEAN Hal_ADC_ReadADCValue( struct HAL_ADC_Self *self, UINT32 *adcValue )
{
    /* this shold use the driver to read the value from the ADC*/
    //defaulting to returning 4V
    *adcValue = 4000;
    return TRUE;
}
