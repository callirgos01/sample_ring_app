#ifndef __OS_ALARM_H__
#define __OS_ALARM_H__

#include "hal/hal_time.h"

#define OS_ALARM_REPEAT_FOREVER ( 255 )
#define OS_ALARM_SECONDS_TO_BEATS(seconds) (seconds * HAL_TIME_BEATSPERSECONDS)

BOOLEAN OS_Alarm_Repeat( Event event, void *data, UINT32 startDelayBeats, UINT32 repeatBeats, UINT8 fireCount );
BOOLEAN OS_Alarm_Set( Event event, void *data, UINT32 startDelayBeats );
void OS_Alarm_Process( void *ignored );

#endif //__OS_ALARM_H__