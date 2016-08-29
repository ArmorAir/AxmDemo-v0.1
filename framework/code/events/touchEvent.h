#ifndef __AM_TOUCH_EVENT__
#define __AM_TOUCH_EVENT__

#include "event.h"
#include "cross\c-define.h"
#include "window\touch.h"

class AM_DLL ATouchEvent : public AEvent {

public:

	Touch* getTouch() const;


private:

	Touch* m_touch;



};







#endif