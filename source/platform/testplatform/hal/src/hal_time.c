
#include "typedefs.h"
#include <stdio.h>
#include <time.h>

void HAL_Time_SetDefaultAlarm( void )
{
    //set the timer to the max amount of time we want to wait when there is nothing wo to do
    //waiting for and interrupt to make us do something else
}
UINT32 HAL_Time_GetBeatsSinceStartup( void )
{
    return clock();
}