#include "typedefs.h"
#include "hal_adc_p.h"
//#include <stdio.h>
//#include <string.h>

void HAL_ADC_CreateSelf( struct HAL_ADC_Self *self )
{
    /*initialize the ADC*/
    //simulating a battery that starts at 4V

    if( self != NULL )
    {
        self->adcValue = 4000;
        self->direction = -1;
    }
}

BOOLEAN Hal_ADC_ReadADCValue( struct HAL_ADC_Self *self, UINT32 *adcValue )
{
    BOOLEAN success = FALSE;
    if( self != NULL )
    {
        if( self->adcValue == 3000 )
        {
            self->direction = 1;
        }
        if( self->adcValue == 4200 )
        {
            self->direction = -1;
        }
        self->adcValue += (self->direction * 100);
        //simulating a battery that is discharging 100 mV every time the battery is read
        *adcValue = self->adcValue;
        success = TRUE;
    }
    return success;
}
