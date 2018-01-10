#ifndef OOPPROJECT_INTERFACES_H
#define OOPPROJECT_INTERFACES_H

#include "types.h"

class ITimedOperation {

public:

	virtual void notify(ID id) = 0;

};

#endif //OOPPROJECT_INTERFACES_H
