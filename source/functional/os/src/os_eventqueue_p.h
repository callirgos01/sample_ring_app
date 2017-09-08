#ifndef __OS_EVENTQUEUE_P_H__
#define __OS_EVENTQUEUE_P_H__

#include "typedefs.h"
#define OS_EventQueue_MAX_EVENTS ( 32 )

#pragma pack(1)
typedef struct
{
    Event events[OS_EventQueue_MAX_EVENTS];
    void *data[OS_EventQueue_MAX_EVENTS];

    UINT8 nextEvent;
    UINT8 eventCount;
} OS_EventQueue_State;
#pragma pack()

#endif // __OS_EVENTQUEUE_P_H__