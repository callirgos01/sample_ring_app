#ifndef __HAL_INTERRUPTS_P_H__
#define __HAL_INTERRUPTS_P_H__
    
extern "C"
{
	void HAL_Interrupts_SetInterruptContext( BOOLEAN context );
	void HAL_Interrupts_WaitForInterrupt( void );
	void HAL_Interrupts_TriggerInterrupt( void );
}

void HAL_Interrupts_SetApplicationThreadId(boost::thread::id id);

#endif // __HAL_INTERRUPTS_P_H__
