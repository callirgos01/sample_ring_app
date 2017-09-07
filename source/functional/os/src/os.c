#include "typedefs.h"

void OS_Enter( void ( *configDefine ) ( void ) )
{
    //HAL_SetDefaultState();
    //OS_Require();
    if ( configDefine != NULL )
    {
        ( *configDefine )();
    }
    //while ( 1 )
    {
        //OS_ProcessOneEvent();
    }
}