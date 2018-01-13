#ifndef OOPPROJECT_NAMECOLLISIONEXCEPTION_H
#define OOPPROJECT_NAMECOLLISIONEXCEPTION_H


#include "ModelException.h"

class NameCollisionException : public ModelException {
public:
	NameCollisionException(const Text &msg, Exception *causedBy = nullptr);

};


#endif //OOPPROJECT_NAMECOLLISIONEXCEPTION_H
