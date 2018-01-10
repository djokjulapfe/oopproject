#ifndef OOPPROJECT_SCHEDULER_H
#define OOPPROJECT_SCHEDULER_H


#include "types.h"

class Event;

class Scheduler {
public:

	static Scheduler *Instance();

	virtual void put(Event *ev);

	virtual Time getCurTime() const;

	virtual bool processNow();

protected:

	Scheduler();

	virtual bool processOneEvent();

private:

	Time curTime;

	Event *first;

};


#endif //OOPPROJECT_SCHEDULER_H
