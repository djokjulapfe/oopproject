#ifndef OOPPROJECT_BADEXPRESSIONEXCEPTION_H
#define OOPPROJECT_BADEXPRESSIONEXCEPTION_H


#include "Exception.h"

class BadExpressionException : public Exception {
public:
	BadExpressionException(const Text &msg, Exception *causedBy = nullptr);

};


#endif //OOPPROJECT_BADEXPRESSIONEXCEPTION_H
