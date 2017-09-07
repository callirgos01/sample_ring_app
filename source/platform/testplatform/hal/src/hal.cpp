extern "C"
{
    #include "../../../../config/config.h"
    #include "../../../../functional/os/os.h"
}

#include "hal_p.hpp"
#include "hal_interrupts_p.hpp"
#include "boost/thread/thread.hpp"
#include "boost/asio/io_service.hpp" 

STATIC boost::thread *s_mainThread = 0;
STATIC boost::thread *s_ioThread = 0;
STATIC boost::asio::io_service *s_ioService;
UINT32 g_halTimeAccelerationFactor = 1;

STATIC struct timeval s_lpModeStart;

extern "C"
{
	void Config_Define( void );
    #define HAL_FAKE_APP_LENGTH ( 1 )
    STATIC UINT8 s_fakeApplicationAndCRC[HAL_FAKE_APP_LENGTH + sizeof(UINT16)];

	UINT8 *HAL_GetApplicationBaseAddress( void )
	{
		return s_fakeApplicationAndCRC;
	}

	UINT32 HAL_GetApplicationLength( void )
	{
		return HAL_FAKE_APP_LENGTH;
	}

    STATIC void HAL_ApplicationThread( void )
    {
        OS_Enter(Config_Define);
    }
}

STATIC void HAL_ApplicationThreadHelper( void )
{
	HAL_Interrupts_SetApplicationThreadId(boost::this_thread::get_id());
	HAL_ApplicationThread();
}

STATIC void HAL_IOThread( void )
{
    boost::asio::io_service &io = HAL_GetIOService();
    io.run();
}

int main( void )
{
    boost::asio::io_service &io = HAL_GetIOService();
    boost::asio::io_service::work work(io);
    boost::thread mainThread(HAL_ApplicationThreadHelper);
    boost::thread ioThread(HAL_IOThread);

    s_mainThread = &mainThread;
    s_ioThread = &ioThread;
    s_mainThread->join();

    // Explicitly stop IO service since "work" was added above
    io.stop();
    s_ioThread->join();

    s_mainThread = NULL;
    s_ioThread = NULL;
    io.reset();

    return 0;
}


boost::asio::io_service &HAL_GetIOService( void )
{
    if (s_ioService == NULL)
    {
        s_ioService = new boost::asio::io_service();
    }
    return *s_ioService;
}
