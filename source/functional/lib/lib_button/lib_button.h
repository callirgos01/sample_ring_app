/* 
    public header for the button identity
*/
#ifndef LIB_BUTTON_H
#define LIB_BUTTON_H

typedef struct Lib_Button_Self Lib_Button_Self;

typedef void ( *Lib_Button_ButtonPressEvent )( void* delegate );
typedef void ( *Lib_Button_ButtonReleasedEvent )( void* delegate );

void Lib_Button_SetButtonPressedCallback( Lib_Button_Self *self, void *delegate, Lib_Button_ButtonPressEvent buttonPressedCallback );
void Lib_Button_SetButtonReleasedCallback( Lib_Button_Self *self, void *delegate, Lib_Button_ButtonReleasedEvent buttonReleasedCallback );

#endif //LIB_BUTTON_H