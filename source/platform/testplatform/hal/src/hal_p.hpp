#ifndef __HAL_P_H__
#define __HAL_P_H__

#include "boost/thread/thread.hpp"
#include "boost/asio/io_service.hpp"

extern UINT32 g_halTimeAccelerationFactor;
boost::thread *HAL_GetMainThread( void );
boost::asio::io_service &HAL_GetIOService( void );

#endif // __HAL_P_H__

