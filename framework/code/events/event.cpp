#include "event.h"




AEvent::AEvent( const char* type ):
	m_type(type),
	m_target(nullptr)
{

}

AEvent::~AEvent() {

}

const char* AEvent::getType() const {
	return m_type;
}

void* AEvent::getTarget() const {
	return m_target;
}

const char* AEvent::toString() const {
	return "aevent";
}

void AEvent::doSetType(char* type) {
	m_type = type;
}

void AEvent::doSetTarget( void* target ) {
	m_target = target;
}



Listener::Listener(int priority):
	m_priority(priority),
	m_prev(nullptr),
	m_next(nullptr),
	m_delayed(false)
{





}

EventDispatcher::EventDispatcher():
	EventDispatcher(nullptr)
{

}

EventDispatcher::EventDispatcher( void* target ):
	m_target(target)
{

}

EventDispatcher::~EventDispatcher() {

}

Listener* EventDispatcher::addEventListener(const char* type, std::function<void(AEvent*)> callback) {
	return this->addEventListener(type, callback, 0);
}

Listener* EventDispatcher::addEventListener(const char* type, std::function<void(AEvent*)> callback, int priority) {
	Listener* listener_A = new Listener(priority);
	listener_A->m_callback = std::move(callback);
	QueueForListener* queue_A = nullptr;
	auto itr = m_lqList.find(type);
	if (itr == m_lqList.end()) {
		queue_A = new QueueForListener();
		m_lqList.insert(std::make_pair(type, queue_A));
	}
	else {
		queue_A = itr->second;
	}
	queue_A->doAddListener(listener_A);

	return listener_A;
}

void EventDispatcher::removeEventListener(Listener* listener) {


}

bool EventDispatcher::hasEventListener(const char* type) {
	return false;
}

void EventDispatcher::dispatchEvent(AEvent* event) {
	QueueForListener* queue_A = nullptr;

	auto itr = m_lqList.find(event->getType());
	if (itr == m_lqList.end()) {
		return;
	}
	else
	{
		queue_A = itr->second;
	}
	event->doSetTarget(m_target);
	queue_A->doExecute(event);

}

void EventDispatcher::dispatch(const char* type) {

}


/*QueueForListener*/

QueueForListener::QueueForListener() :
	m_begin(new Listener(0)),
	m_curr(nullptr),
	m_end(nullptr)
{

}

QueueForListener::~QueueForListener() {

}


void QueueForListener::doAddListener(Listener* listener) {
	Listener* LA = nullptr;

	listener->m_delayed = m_curr && (m_curr == m_begin || listener->m_priority <= m_curr->m_priority);
	if (!m_end) {
		listener->m_prev = m_begin;
		m_begin->m_next = m_end = listener;
	}
	else if (listener->m_priority <= m_end->m_priority) {
		listener->m_prev = m_end;
		m_end->m_next = listener;
		m_end = listener;
	}
	else {
		LA = m_end->m_prev;
		while (LA != m_begin && listener->m_priority > LA->m_priority) {
			LA = LA->m_prev;
		}
		listener->m_prev = LA;
		if (LA->m_next) {
			listener->m_next = LA->m_next;
			LA->m_next = LA->m_next->m_prev = listener;
		}
		else {
			LA->m_next = listener;
		}
	}
}


void QueueForListener::doRemoveListener(Listener* v) {
	



}


void QueueForListener::doExecute(AEvent* event) {
	m_curr = m_begin->m_next;
	while (m_curr) {
		if (m_curr->m_delayed) {
			m_curr->m_delayed = false;
		}
		else {
			m_curr->m_callback(event);
		}
		m_curr = m_curr ? m_curr->m_next : nullptr;
	}


}


void QueueForListener::doStopPropagation() {




}



void QueueForListener::doDispose() {




}


