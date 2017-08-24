
#ifndef __LIB_LED_H__
#define __LIB_LED_H__

#include "typedefs.h"

typedef struct Lib_LED_Self Lib_LED_Self;

void Lib_LED_TurnLEDOn( Lib_LED_Self *self );
void Lib_LED_TurnLEDOff( Lib_LED_Self *self );
void Lib_LED_StartPattern( Lib_LED_Self *self, UINT32 miliSecondsOnTime, UINT32 miliSecondsOffTime );
void Lib_LED_StopPattern( Lib_LED_Self *self );

#endif // __LIB_LED_H__
