#ifndef __AA_EVENT__
#define __AA_EVENT__

#include <iostream>
#include <unordered_map>
//#include <string>
#include <functional>

#include "cross\define.h"


class QueueForListener;



class AA_DLL AEvent {

public:

	AEvent( const char* type );
	virtual ~AEvent();

	const char* getType() const;
	void* getTarget() const;
	virtual const char* AEvent::toString() const;

	void doSetType(char* type);
	void doSetTarget( void* target );

protected:

	const char* m_type;
	void* m_target;
};



class AA_DLL Listener {

public:
	Listener(int priority);

	std::function<void(AEvent*)> m_callback;
	int m_priority;
	Listener* m_prev;
	Listener* m_next;
	bool m_delayed;
};



class AA_DLL EventDispatcher {

public:

	EventDispatcher();
	EventDispatcher( void* target );
	~EventDispatcher();

	Listener* addEventListener(const char* type, std::function<void(AEvent*)> callback, int priority = 0);
	void removeEventListener(Listener* listener);
	void dispatchEvent(AEvent* event);

protected:

	void* m_target;
	std::unordered_map<const char*, QueueForListener*> m_lqList{};

};



////////////////////////
// internal
////////////////////////

class AA_DLL QueueForListener {

public:

	QueueForListener();
	~QueueForListener();

	void doAddListener(Listener* listener);
	void doRemoveListener(Listener* listener);
	void doExecute(AEvent* listener);
	void doStopPropagation();
	void doDispose();

private:

	Listener* m_begin;
	Listener* m_end;
	Listener* m_curr;
};





#endif // !__AA_AEVENT__
