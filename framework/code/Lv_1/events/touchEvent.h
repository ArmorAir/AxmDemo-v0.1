#ifndef __AM_TOUCH_EVENT__
#define __AM_TOUCH_EVENT__

#include "Lv_0\events\event.h"
#include "Lv_1\cross\c-define.h"
#include "Lv_1\window\touch.h"

class AM_DLL ATouchEvent : public AEvent {

public:

	Touch* getTouch() const;


private:

	Touch* m_touch;



};







#endif