#include "Scheduler.h"
#include "Event.h"

Scheduler *Scheduler::Instance() {
	static Scheduler instance;
	return &instance;
}

void Scheduler::put(Event *ev) {
	if (ev == nullptr) return;
	Time time = ev->getTime();
	Event *nxt = first;
	Event *prv = nullptr;

	while (nxt != nullptr && time >= nxt->getTime()) {
		time -= nxt->getTime();
		prv = nxt;
		nxt = nxt->getNext();
	}

	if (nxt) nxt->setTime(nxt->getTime() - time);
	ev->setTime(time);
	ev->setNext(nxt);
	if (prv != 0) prv->setNext(ev); else first = ev;
}

Time Scheduler::getCurTime() const {
	return curTime;
}

Scheduler::Scheduler() : curTime(0), first(nullptr) {
}

bool Scheduler::processOneEvent() {
	Event *ev = first;
	if (ev == 0) return false;
	first = first->getNext();
	curTime += ev->getTime();
	ITimedOperation *el = ev->getTarget();
	if (el) el->notify(ev->getId());
	delete ev;
	return (first && first->getTime() == 0);
}

bool Scheduler::processNow() {
	while (processOneEvent());
	return (first != nullptr);
}
