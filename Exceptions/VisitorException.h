#ifndef OOPPROJECT_VISITOREXCEPTION_H
#define OOPPROJECT_VISITOREXCEPTION_H


#include "Exception.h"

class VisitorException : public Exception {
public:
	VisitorException(const Text &msg, Exception *causedBy = nullptr);

};


#endif //OOPPROJECT_VISITOREXCEPTION_H
