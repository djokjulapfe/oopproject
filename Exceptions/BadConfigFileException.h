#ifndef OOPPROJECT_BADCONFIGFILEEXCEPTION_H
#define OOPPROJECT_BADCONFIGFILEEXCEPTION_H


#include "ModelException.h"

class BadConfigFileException : public ModelException {
public:
	BadConfigFileException(const Text &msg, Exception *causedBy = nullptr);

};


#endif //OOPPROJECT_BADCONFIGFILEEXCEPTION_H
