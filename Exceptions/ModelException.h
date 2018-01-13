#ifndef OOPPROJECT_MODELEXCEPTION_H
#define OOPPROJECT_MODELEXCEPTION_H


#include "Exception.h"

class ModelException : public Exception {
public:
	ModelException(const Text &msg, Exception *causedBy = nullptr);

};


#endif //OOPPROJECT_MODELEXCEPTION_H
