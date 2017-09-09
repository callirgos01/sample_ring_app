/*
    File containig global definition of types used throughout the project
*/
#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdint.h>

typedef volatile void ( *InterruptEvent )( void *data );

typedef signed int      SINT32;  // 32 bits
typedef uint8_t         BOOLEAN; //  8 bits - use TRUE or FALSE for this type
typedef unsigned char   UINT8;   //  8 bits
typedef unsigned short  UINT16;  // 16 bits
typedef unsigned int    UINT32;  // 32 bits
typedef void ( *Event )( void *data );

// in case we ever want to remove the static tag from all the declartions
#define STATIC static

#ifndef TRUE
#define TRUE   ( ( BOOLEAN )1 )
#endif
#ifndef FALSE
#define FALSE  ( ( BOOLEAN )0 )
#endif

#ifndef NULL
#define NULL ( ( void * ) 0 )
#endif // !defined(NULL)

#endif//TYPEDEFS_H