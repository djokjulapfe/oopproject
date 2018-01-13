#ifndef OOPPROJECT_VARNOTAVAILABLEEXCEPTION_H
#define OOPPROJECT_VARNOTAVAILABLEEXCEPTION_H


#include "MemoryException.h"

class VarNotAvailableException : public MemoryException {

public:

	VarNotAvailableException(const Text &msg, Exception *causedBy = nullptr);

};


#endif //OOPPROJECT_VARNOTAVAILABLEEXCEPTION_H
