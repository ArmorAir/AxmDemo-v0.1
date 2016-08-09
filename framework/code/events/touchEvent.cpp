
#include "touchEvent.h"



ATouchEvent::ATouchEvent(const char* type) :
	AEvent(type)
{
	m_type;
}

int ATouchEvent::getTouch() {
	return 333;
}