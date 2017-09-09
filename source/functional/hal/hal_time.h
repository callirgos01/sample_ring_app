#ifndef __HAL_TIME_H__
#define __HAL_TIME_H__

#include <time.h>

#define HAL_TIME_BEATSPERSECONDS ( CLOCKS_PER_SEC )

UINT32 HAL_Time_GetBeatsSinceStartup( void );
void HAL_Time_SetDefaultAlarm( void );

#endif //__HAL_TIME_H__