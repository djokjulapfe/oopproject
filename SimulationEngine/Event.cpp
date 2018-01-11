#include "Event.h"
#include "Scheduler.h"
#include "../Software/Machine.h"

Event::Event(ITimedOperation *targetOperation, Time tm, ID id)
		: id(id), time(tm), next(nullptr), target(targetOperation) {
	Scheduler::Instance()->put(this);
	//startTime = Scheduler::Instance()->getCurTime();
	// TODO: maby only use one variable?
	targetOperation->startTime = Scheduler::Instance()->getCurTime();
	Machine::Instance()->toExecute(targetOperation);
}

void Event::create(ITimedOperation *timedOperation, Time tm, ID id) {
	new Event(timedOperation, tm, id);
}

ID Event::getId() const {
	return id;
}

ITimedOperation *Event::getTarget() const {
	return target;
}

Time Event::getTime() const {
	return time;
}

Event *Event::getNext() const {
	return next;
}

void Event::setTime(Time time) {
	Event::time = time;
}

void Event::setNext(Event *next) {
	Event::next = next;
}
