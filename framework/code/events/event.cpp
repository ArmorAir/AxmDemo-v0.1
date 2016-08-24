#include "event.h"



//-------------------------------
// AEvent
//-------------------------------

AEvent::AEvent(void* target) :
	m_begin(new Listener(this, 0)),
	m_curr(nullptr),
	m_end(nullptr),
	m_target(target),
	m_userData(nullptr)
{

}

AEvent::AEvent() :
	AEvent(nullptr)
{

}

Listener* AEvent::createListener(std::function<void(AEvent*)> callback, int priority) {
	Listener* LA    =  nullptr;
	Listener* LB    =  new Listener(this, priority);
	LB->m_callback  =  std::move(callback);
	LB->m_delayed   =  m_curr && (m_curr == m_begin || LB->m_priority <= m_curr->m_priority);
	if (!m_end) {
		LB->m_prev       =  m_begin;
		m_begin->m_next  =  m_end = LB;
	}
	else if (LB->m_priority <= m_end->m_priority) {
		LB->m_prev     =  m_end;
		m_end->m_next  =  LB;
		m_end          =  LB;
	}
	else {
		LA = m_end->m_prev;
		while (LA != m_begin && LB->m_priority > LA->m_priority) {
			LA = LA->m_prev;
		}
		LB->m_prev = LA;
		if (LA->m_next) {
			LB->m_next  =  LA->m_next;
			LA->m_next  =  LA->m_next->m_prev = LB;
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

void AEvent::kill() {
	this->doDispose();
}

void AEvent::doDispose() {
	Listener* curr = nullptr;
	Listener* next = m_begin->m_next;
	delete m_begin;
	while (next) {
		curr = next;
		next = curr->m_next;
		delete curr;
	}
	delete this;
}

void AEvent::doDestroyListener(Listener* LA) {
	if (LA == m_curr) {
		m_curr = LA->m_prev;
	}
	if (LA == m_end) {
		m_end = (LA->m_prev == m_begin) ? nullptr : LA->m_prev;
	}
	LA->m_prev->m_next = LA->m_next;
	if (LA->m_next) {
		LA->m_next->m_prev = LA->m_prev;
	}
	delete LA;
}



//-------------------------------
// Listener
//-------------------------------

Listener::Listener(AEvent* evt, int priority) :
	m_event(evt),
	m_priority(priority),
	m_prev(nullptr),
	m_next(nullptr),
	m_delayed(false)
{

}

AEvent* Listener::getEvent() {
	return m_event;
}

void Listener::kill() {
	m_event->doDestroyListener(this);
}
