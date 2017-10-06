/*
    this file should configure everything that has to do with the ethernet connection
*/
#include "typedefs.h"

#include "lib_ethernet/src/lib_ethernet_config.h"
#include "hal/hal_ethernet.h"
#include "hal/src/hal_ethernet_config.h"

#define TEST_SERVER_NAME_LENGTH 14
#define TEST_SERVER "test.ring.com"
#define TEST_PORT  13469

STATIC BOOLEAN s_configEthernetLoaded = FALSE;

STATIC Lib_Ethernet_Self s_ethernetSelf;
STATIC HAL_Ethernet_Self s_halEthernetSelf;

STATIC void Config_Ethernet_Init( void )
{
    HAL_Ethernet_CreateSelf( &s_halEthernetSelf );
    
    HAL_Ethernet_Configure( &s_halEthernetSelf, TEST_SERVER, TEST_SERVER_NAME_LENGTH, TEST_PORT);
    
    Lib_Ethernet_CreateSelf( &s_ethernetSelf, &s_halEthernetSelf );
}
Lib_Ethernet_Self *Config_Ethernet_GetEthernetSelf( void )
{
    if( s_configEthernetLoaded != TRUE )
    {
        s_configEthernetLoaded = TRUE;
        Config_Ethernet_Init();
    }
    return &s_ethernetSelf;

}
