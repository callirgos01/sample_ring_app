#ifndef __OS_ALARM_H__
#define __OS_ALARM_H__

#include "hal/hal_time.h"

#define OS_ALARM_REPEAT_FOREVER ( 255 )
#define MILISECONDS_PER_SECOND ( 1000 )

#define OS_ALARM_SECONDS_TO_BEATS(seconds) (UINT32)( seconds * ( HAL_TIME_BEATSPERSECONDS )  )
#define OS_ALARM_BEATS_TO_MILISECONDS(beats) ( beats / ( HAL_TIME_BEATSPERSECONDS / MILISECONDS_PER_SECOND) )
/*
this implementation would allow us to pass seconds worth of miliseconds
but it would require us to use doubles
if we stay with Unsinged integers we can determine beats more efficiently.
but we wont be able to get beats out of seconds worth of miliseoncdes.
for this just use the seconds to beats function
#define OS_ALARM_MILISECONDS_TO_BEATS(mseconds) ( OS_ALARM_SECONDS_TO_BEATS( (double)((double)mseconds / (double)MILISECONDS_PER_SECOND)))
*/
#define OS_ALARM_MILISECONDS_TO_BEATS(mseconds) ((mseconds * HAL_TIME_BEATSPERSECONDS) / MILISECONDS_PER_SECOND)
BOOLEAN OS_Alarm_Repeat( Event event, void *data, UINT32 startDelayBeats, UINT32 repeatBeats, UINT8 fireCount );
BOOLEAN OS_Alarm_Set( Event event, void *data, UINT32 startDelayBeats );
void OS_Alarm_Process( void *ignored );
void OS_Alarm_Cancel( Event eventToRemove, void *dataToRemove );

#endif //__OS_ALARM_H__


//500 * 1/1000 * 1000000000

//500 * 1000000000 * 1/1000