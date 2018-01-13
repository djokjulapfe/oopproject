#ifndef OOPPROJECT_EXCEPTION_H
#define OOPPROJECT_EXCEPTION_H

#include "../Utils/utils.h"

class Exception : public std::exception {

public:

	Exception(const Text &msg, Exception *causedBy = nullptr);

	const char *what() const noexcept override;

protected:

	Exception *causedBy;

	Text msg;
};


#endif //OOPPROJECT_EXCEPTION_H
