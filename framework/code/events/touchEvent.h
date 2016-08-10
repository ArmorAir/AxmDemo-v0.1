#ifndef __AA_TOUCH_EVENT__
#define __AA_TOUCH_EVENT__

#include "event.h"


class AA_DLL ATouchEvent : public AEvent {

public:

	ATouchEvent( const char* type );

	virtual const char* toString() const;

};







#endif // !__AA_TOUCH_EVENT__