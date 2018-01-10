#ifndef OOPPROJECT_TOKEN_H
#define OOPPROJECT_TOKEN_H


#include "../Utils/types.h"
#include "Operation.h"

class Token {

public:

	Token(double value);

	Token();

	double getValue() const;

	void setValue(double value);

private:

	Text name;

	Operation *producedBy;

public:
	double value;
};


#endif //OOPPROJECT_TOKEN_H
