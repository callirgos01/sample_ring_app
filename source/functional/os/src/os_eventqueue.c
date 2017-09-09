#include "typedefs.h"
#include "os_eventqueue_p.h"
#include "../os_alarm.h"

STATIC OS_EventQueue_State s_eventQueueState;
STATIC BOOLEAN s_osEventQueueLoaded = FALSE;
STATIC BOOLEAN s_alarmProcessQueued = FALSE;

STATIC void OS_EventQueue_Init( void )
{
    UINT16 i;
    //make atomic
    //diable interrupts here
    s_eventQueueState.eventCount = 0;
    s_eventQueueState.nextEvent = 0;

    for ( i = 0; i < OS_EventQueue_MAX_EVENTS; i++ )
    {
        s_eventQueueState.events[i] = NULL;
        s_eventQueueState.data[i] = NULL;
    }
    //re enable interrupts here

    //might need to create queue locks here, but we might not

}
void OS_EventQueue_Require( void )
{
    if ( s_osEventQueueLoaded != TRUE )
    {
        s_osEventQueueLoaded = TRUE;
        OS_EventQueue_Init();
    }
}
STATIC Event OS_EventQueue_DequeueHelper( void **dataPtr )
{
    Event eventRemoved = NULL;

    if( s_eventQueueState.eventCount > 0 )
    {
        eventRemoved = s_eventQueueState.events[s_eventQueueState.nextEvent];
        if( dataPtr != NULL )
        {
            *dataPtr = s_eventQueueState.data[s_eventQueueState.nextEvent];
        }
        s_eventQueueState.events[s_eventQueueState.nextEvent] = NULL;
        s_eventQueueState.data[s_eventQueueState.nextEvent] = NULL;
        s_eventQueueState.nextEvent = (UINT8)( ( s_eventQueueState.nextEvent + 1 ) % OS_EventQueue_MAX_EVENTS );
        s_eventQueueState.eventCount--;
    }
    if ( eventRemoved == OS_Alarm_Process )
    {
        s_alarmProcessQueued = FALSE;
    }
    
    return ( eventRemoved );
}
Event OS_EventQueue_Dequeue( void **dataPtr )
{
    Event eventRemoved;
    //make this atomic
    //disable interrupts here
    OS_EventQueue_Require();
    eventRemoved = OS_EventQueue_DequeueHelper( dataPtr );
    //re enable interrupts
    return eventRemoved;
}
STATIC BOOLEAN OS_EventQueue_QueueHelper( Event event, void *data )
{
    BOOLEAN success = TRUE;
    if( (event != OS_Alarm_Process) || (s_alarmProcessQueued == FALSE) )
    {
        if( s_eventQueueState.eventCount < OS_EventQueue_MAX_EVENTS )
        {
            UINT16 index = ( s_eventQueueState.nextEvent + s_eventQueueState.eventCount ) % OS_EventQueue_MAX_EVENTS;
            s_eventQueueState.events[index] = event;
            s_eventQueueState.data[index] = data;
            s_eventQueueState.eventCount++;
            if ( event == OS_Alarm_Process )
            {
                s_alarmProcessQueued = TRUE;
            }
        }
        else
        {
            success = FALSE;
        }
    }
    return success;

}
BOOLEAN OS_EventQueue_Queue( Event event, void *data )
{
    BOOLEAN eventAdded = FALSE;
    if( event != NULL )
    {
        //make this atomic
        //stop interrupts here
        OS_EventQueue_Require();
        eventAdded = OS_EventQueue_QueueHelper( event, data );
        //re enable interrupts here
    }
    return eventAdded;
}