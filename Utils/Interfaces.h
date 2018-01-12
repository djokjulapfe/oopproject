#ifndef OOPPROJECT_INTERFACES_H
#define OOPPROJECT_INTERFACES_H

#include "utils.h"

class ITimedOperation {

public:

	virtual void notify(ID id) = 0;

	Time opTime;

	Time startTime;

};

#endif //OOPPROJECT_INTERFACES_H
