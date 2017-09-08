#include "typedefs.h"
#include "../os_eventqueue.h"

STATIC BOOLEAN s_OSloaded = FALSE;

void OS_Init( void )
{
    //intialize interrupt system (boost or hardware)
    s_OSloaded = TRUE;
}

void OS_Require( void )
{
    if ( s_OSloaded == FALSE )
    {
        OS_Init();
    }
}

STATIC void OS_ProcessOneEvent( void )
{
    Event nextEvent;
    void *data;
    
    //@todo figure out a way to make this atomic
    //disable interrupts here 
    nextEvent = OS_EventQueue_Dequeue( &data );

    if( nextEvent != NULL )
    {   
        //re enable interrupts here
        ( *nextEvent )( data );
    }
    else
    {
        //go idle in some way
        //enable interrupts again
    }
    //process alarms here, once we add an alarm process
}

void OS_Enter( void ( *configDefine ) ( void ) )
{
    //HAL_SetDefaultState();
    OS_Require();
    if ( configDefine != NULL )
    {
        ( *configDefine )();
    }
    while ( 1 )
    {
        OS_ProcessOneEvent();
    }
}