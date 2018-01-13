#ifndef OOPPROJECT_INDEXOUTOFBOUNDSEXCEPTION_H
#define OOPPROJECT_INDEXOUTOFBOUNDSEXCEPTION_H


#include "Exception.h"

class IndexOutOfBoundsException : Exception {
public:
	IndexOutOfBoundsException(const Text &msg, Exception *causedBy = nullptr);

};


#endif //OOPPROJECT_INDEXOUTOFBOUNDSEXCEPTION_H
