#ifndef OOPPROJECT_MEMORYEXCEPTION_H
#define OOPPROJECT_MEMORYEXCEPTION_H

#include "../Utils/utils.h"
#include "Exception.h"

class MemoryException : public Exception {
public:
	MemoryException(const Text &msg, Exception *causedBy = nullptr);
};


#endif //OOPPROJECT_MEMORYEXCEPTION_H
