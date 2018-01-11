#ifndef OOPPROJECT_TOKEN_H
#define OOPPROJECT_TOKEN_H


#include "../Utils/types.h"
#include "Operation.h"

class Token {

public:

	explicit Token(double value, Text name = "Unnamed Token");

	Token();

	double getValue() const;

	const Text &getName() const;

	void setName(const Text &name);

	void setValue(double value);

private:

	Text name;

	Operation *producedBy;

public:
	double value;
};


#endif //OOPPROJECT_TOKEN_H
