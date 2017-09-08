#ifndef __OS_EVENTQUEUE_H__
#define __OS_EVENTQUEUE_H__
#include "typedefs.h"

Event OS_EventQueue_Dequeue( void **dataPtr );
BOOLEAN OS_EventQueue_Queue( Event event, void *data );

#endif // __OS_EVENTQUEUE_H__