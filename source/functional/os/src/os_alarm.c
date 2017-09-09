
#include "typedefs.h"
#include <stdio.h>
#include "os_alarm_p.h"
#include "../os_alarm.h"
#include "hal/hal_time.h"
#include "../os_eventqueue.h"
STATIC OS_Alarm_State s_alarmState;
STATIC BOOLEAN s_osAlarmLoaded = FALSE;
STATIC SINT32 OS_Alarm_TimeDiff( UINT32 left, UINT32 right )
{
    SINT32 diff = (SINT32)(left - right);
    return diff;
}
STATIC void OS_Alarm_InitAlarmStruct( OS_Alarm_AlarmStruct* alarmStruct )
{
    alarmStruct->targetBeats = 0;
    alarmStruct->repeatBeats = 0;
    alarmStruct->fireCount = 0;
    alarmStruct->event = NULL;
    alarmStruct->data = NULL;
}

STATIC void OS_Alarm_Init( void )
{
    UINT32 i;
    s_alarmState.activeAlarmCount = 0;
    for ( i = 0; i < OS_ALARM_MAX_ALARMS; i++ )
    {
        OS_Alarm_InitAlarmStruct( &s_alarmState.alarms[i] );
    }

    s_osAlarmLoaded = TRUE;
}

STATIC void OS_Alarm_Require( void )
{
    if ( s_osAlarmLoaded != TRUE )
    {
        OS_Alarm_Init();
    }
}

BOOLEAN OS_Alarm_Repeat( Event event, void *data, UINT32 startDelayBeats, UINT32 repeatBeats, UINT8 fireCount )
{
    printf("startDelayBeats %u\r\n", startDelayBeats);
    printf("repeatBeats %u\r\n", repeatBeats);
    printf("fireCount %u\r\n", fireCount);
    BOOLEAN alarmAdded = FALSE;
    UINT32 i;
    OS_Alarm_Require();
    for ( i = 0; ( ( alarmAdded != TRUE ) && ( i < OS_ALARM_MAX_ALARMS ) ); i++ )
    {
        OS_Alarm_AlarmStruct *alarm = &s_alarmState.alarms[i];
        if( alarm->event == NULL )
        {
            alarm->event = event;
            alarm->data = data;
            alarm->targetBeats = HAL_Time_GetBeatsSinceStartup() + startDelayBeats;
            alarm->repeatBeats = repeatBeats;
            alarm->fireCount = fireCount;
            alarmAdded = TRUE;

            if( (s_alarmState.activeAlarmCount == 0) || (OS_Alarm_TimeDiff( alarm->targetBeats, s_alarmState.nextAlarmBeats)< 0) )
            {
                s_alarmState.nextAlarmBeats = alarm->targetBeats;
            }
            s_alarmState.activeAlarmCount++;
        }
    }
    OS_EventQueue_Queue( OS_Alarm_Process, NULL );
    return alarmAdded;
}

BOOLEAN OS_Alarm_Set( Event event, void *data, UINT32 startDelayBeats )
{
    printf("beats to wait %u\r\n", startDelayBeats);
    return OS_Alarm_Repeat( event, data, startDelayBeats, 0, 1 );
}

void OS_Alarm_Process( void *ignored )
{
    UINT32 i;
    UINT32 nowBeats = HAL_Time_GetBeatsSinceStartup();

    OS_Alarm_Require( );

    if( (s_alarmState.activeAlarmCount != 0) && (OS_Alarm_TimeDiff(s_alarmState.nextAlarmBeats, nowBeats) <= 0) )
    {
        s_alarmState.activeAlarmCount = 0;
        for( i = 0; i < OS_ALARM_MAX_ALARMS; i++ )
        {
            OS_Alarm_AlarmStruct *alarm = &s_alarmState.alarms[i];
            while( (alarm->event != NULL) && (OS_Alarm_TimeDiff( alarm->targetBeats, nowBeats ) <= 0) ) 
            {
                OS_EventQueue_Queue( alarm->event, alarm->data );
                if( alarm->fireCount > 1 )
                {
                    if( alarm->fireCount != OS_ALARM_REPEAT_FOREVER )
                    {
                        alarm->fireCount--;
                    }
                    alarm->targetBeats += alarm->repeatBeats;
                }
                else
                {
                    OS_Alarm_InitAlarmStruct( alarm );
                }
            }
            if( alarm->event != NULL )
            {
                if ( ( s_alarmState.activeAlarmCount == 0 ) || ( OS_Alarm_TimeDiff( alarm->targetBeats, s_alarmState.nextAlarmBeats ) < 0 ) )
                {
                    s_alarmState.nextAlarmBeats = alarm->targetBeats;
                }
                s_alarmState.activeAlarmCount++;
            }
        }
    }
    
    if ( s_alarmState.activeAlarmCount != 0 )
    {
        UINT32 nowBeats = HAL_Time_GetBeatsSinceStartup();
        SINT32 timeToNext = OS_Alarm_TimeDiff( s_alarmState.nextAlarmBeats, nowBeats );

        if ( timeToNext <= 0 )
        {
            OS_EventQueue_Queue( OS_Alarm_Process, NULL );
        }
        else
        {
            //need a hal backed alarm system
            //for now just have the while loop stay on, and checking time constantly
            //HAL_Time_SetAlarmBeats( timeToNext );
        }
    }
    else
    {
        HAL_Time_SetDefaultAlarm();
    }
}