#ifndef __AA_EVENT__
#define __AA_EVENT__

#include <iostream>
#include <unordered_map>
//#include <string>
#include <functional>


#if defined(_USRDLL)
	#define AA_DLL     __declspec(dllexport)
#else
	#define AA_DLL     __declspec(dllimport)
#endif



class QueueForListener;



class AA_DLL AEvent {

public:

	AEvent( char* type = nullptr );
	~AEvent();


	char* getType() const;
	void* getTarget() const;

	void doSetType(char* type);
	void doSetTarget( void* target );

protected:

	char* m_type;
	void* m_target;

};


class AA_DLL Listener {

public:
	Listener();
	Listener(std::function<void(AEvent*)> listener, void* invoker, int priority);

	std::function<void(AEvent*)> m_listener;
	void* m_invoker;
	int m_priority;

	Listener* m_prev;
	Listener* m_next;
	bool m_delayed;



};



class AA_DLL EventDispatcher {

public:

	EventDispatcher( void* target = nullptr );
	~EventDispatcher();

	
	Listener* addEventListener(const char* type, std::function<void(AEvent*)> callback, void* invoker = nullptr, int priority = 0);
	void removeEventListener(Listener* v);
	void dispatchEvent(AEvent* event);


protected:

	void* m_target;
	std::unordered_map<const char*, QueueForListener*> m_lqList;

};




////////////////////////
// internal
////////////////////////

class AA_DLL QueueForListener {

public:

	QueueForListener();
	~QueueForListener();

	void doAddListener(Listener* v);
	void doRemoveListener(Listener* v);
	void doExecute(AEvent* v);
	void doStopPropagation();
	void doDispose();

private:

	Listener* m_begin;
	Listener* m_end;
	Listener* m_curr;


};





#endif // !__AA_AEVENT__
