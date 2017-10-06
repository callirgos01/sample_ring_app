
#ifndef __LIB_CHARGER_P_H__
#define __LIB_CHARGER_P_H__

#include "typedefs.h"
#include "lib_charger/lib_charger.h"
#include "hal/hal_gpio.h"

struct Lib_Charger_Self
{    
    void* delegate;
    HAL_GPIO_Self *chargerConnectedInterrupt;
    Lib_Charger_ChargerConnectedEvent chargerConnected;
    Lib_Charger_ChargerDisconnectedEvent chargerDisconnected;
};

#endif // __LIB_CHARGER_P_H__
