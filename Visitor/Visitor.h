#ifndef OOPPROJECT_IVISITOR_H
#define OOPPROJECT_IVISITOR_H


#include "../Hardware/Hardware.h"

class Visitor {

public:

	virtual void visitAdd(AddOperation *operation) = 0;

	virtual void visitMult(MultOperation *operation) = 0;

	virtual void visitExp(ExpOperation *operation) = 0;

	virtual void visitMemoryRead(MemoryReadOperation *operation) = 0;

	virtual void visitMemoryWrite(MemoryWriteOperation *operation) = 0;
};


#endif //OOPPROJECT_IVISITOR_H
