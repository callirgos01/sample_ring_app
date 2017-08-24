/*
    public header of the ring app
    all public interface functions will be prototyped here 
*/
#ifndef LIB_RINGAPP_H
#define LIB_RINGAPP_H

//forward declaration of the set structure
//allows the public interface from revealing the content of the self
typedef struct Lib_RingApp_Self Lib_RingApp_Self;

void Lib_RingApp_Start( Lib_RingApp_Self *self );

#endif//LIB_RINGAPP_H