#ifndef OOPPROJECT_MEMORYOPERATION_H
#define OOPPROJECT_MEMORYOPERATION_H


#include "Operation.h"
#include "../Software/Memory.h"

class MemoryOperation : public Operation {

	/**
	 * @brief Intermediary class for operation that use memory
	 */

public:

	Memory::Thread *owningThread;

protected:

	explicit MemoryOperation(Text name = "Memory Operation");

};


#endif //OOPPROJECT_MEMORYOPERATION_H
