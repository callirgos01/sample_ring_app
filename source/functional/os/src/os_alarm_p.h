#ifndef __OS_ALARM_P_H__
#define __OS_ALARM_P_H__

#define OS_ALARM_MAX_ALARMS ( 50 )

#pragma pack(1)
typedef struct
{
    Event event;
    void *data;
    UINT32 targetBeats;
    UINT32 repeatBeats;
    UINT8 fireCount;
} OS_Alarm_AlarmStruct;

typedef struct
{
    UINT8 activeAlarmCount;
    UINT32 nextAlarmBeats;
    OS_Alarm_AlarmStruct alarms[OS_ALARM_MAX_ALARMS];
} OS_Alarm_State;
#pragma pack()

#endif //__OS_ALARM_P_H__