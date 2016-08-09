#ifndef __AA_TOUCH_EVENT__
#define __AA_TOUCH_EVENT__

#include "event.h"


class AA_DLL ATouchEvent : public AEvent {

public:

	ATouchEvent( const char* type );

	int getTouch();

};







#endif // !__AA_TOUCH_EVENT__