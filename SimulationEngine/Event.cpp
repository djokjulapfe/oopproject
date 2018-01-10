#include "Event.h"
#include "Scheduler.h"

Event::Event(ITimedOperation *targetOperation, Time tm, ID id)
		: id(id), time(tm), next(nullptr), target(targetOperation) {
	Scheduler::Instance()->put(this);
	startTime = Scheduler::Instance()->getCurTime();
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

Time Event::getStartTime() const {
	return startTime;
}
