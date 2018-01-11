#ifndef OOPPROJECT_MEMORYOPERATION_H
#define OOPPROJECT_MEMORYOPERATION_H


#include "Operation.h"
#include "../Software/Memory.h"

class MemoryOperation : public Operation {

public:

	Memory::Thread *owningThread;

protected:

	explicit MemoryOperation(Text name = "Memory Operation");

	// TODO: add MemoryReadOperation

};


#endif //OOPPROJECT_MEMORYOPERATION_H
