
#include "touchEvent.h"



ATouchEvent::ATouchEvent(const char* type) :
	AEvent(type)
{
	m_type;
}

const char* ATouchEvent::toString() const {
	return "atouchevent";
}