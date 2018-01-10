#ifndef OOPPROJECT_EVENT_H
#define OOPPROJECT_EVENT_H

#include "../Utils/types.h"
#include "../Utils/Interfaces.h"

class Event {

public:

	static void create(ITimedOperation *timedOperation, Time tm, ID id = 0);

	virtual ID getId() const;

	Time getTime() const;

	Event *getNext() const;

	ITimedOperation *getTarget() const;

	void setTime(Time time);

	Time getStartTime() const;

	void setNext(Event *next);

protected:

	Event(ITimedOperation *targetOperation, Time tm, ID id = 0);

private:

	ID id;

	Time time;

	Time startTime;

	Event *next;

	ITimedOperation *target;

};


#endif //OOPPROJECT_EVENT_H
