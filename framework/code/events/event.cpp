#include "event.h"



Listener::Listener(int priority) :
	m_priority(priority),
	m_prev(nullptr),
	m_next(nullptr),
	m_delayed(false)
{

}

AEvent::AEvent(void* target) :
	m_begin(new Listener(0)),
	m_curr(nullptr),
	m_end(nullptr),
	m_target(target),
	m_tag(nullptr),
	m_userData(nullptr)
{

}

AEvent::AEvent() :
	AEvent(nullptr)
{

}

AEvent::~AEvent() {

}

Listener* AEvent::createListener(std::function<void(AEvent*)> callback, int priority) {
	Listener* LB = new Listener(priority);
	LB->m_callback = std::move(callback);
	Listener* LA = nullptr;

	LB->m_delayed = m_curr && (m_curr == m_begin || LB->m_priority <= m_curr->m_priority);
	if (!m_end) {
		LB->m_prev = m_begin;
		m_begin->m_next = m_end = LB;
	}
	else if (LB->m_priority <= m_end->m_priority) {
		LB->m_prev = m_end;
		m_end->m_next = LB;
		m_end = LB;
	}
	else {
		LA = m_end->m_prev;
		while (LA != m_begin && LB->m_priority > LA->m_priority) {
			LA = LA->m_prev;
		}
		LB->m_prev = LA;
		if (LA->m_next) {
			LB->m_next = LA->m_next;
			LA->m_next = LA->m_next->m_prev = LB;
		}
		else {
			LA->m_next = LB;
		}
	}
	return LB;
}

Listener* AEvent::createListener(std::function<void(AEvent*)> callback) {
	return this->createListener(callback, 0);
}

void AEvent::trigger() {
	m_curr = m_begin->m_next;
	while (m_curr) {
		if (m_curr->m_delayed) {
			m_curr->m_delayed = false;
		}
		else {
			m_curr->m_callback(this);
		}
		m_curr = m_curr ? m_curr->m_next : nullptr;
	}
}

void* AEvent::getTarget() const {
	return m_target;
}

void AEvent::setTarget(void* v) {
	m_target = v;
}

const char* AEvent::getTag() const {
	return m_tag;
}

void AEvent::setTag(const char* v) {
	m_tag = v;
}

void* AEvent::getUserData() const {
	return m_userData;
}

void AEvent::setUserData(void* v) {
	m_userData = v;
}

void AEvent::stopPropagation() {
	while (m_curr) {
		m_curr->m_delayed = false;
		m_curr = m_curr->m_next;
	}
}

void AEvent::dispose() {

}
