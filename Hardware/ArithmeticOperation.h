#ifndef OOPPROJECT_ARITHMETICOPERATION_H
#define OOPPROJECT_ARITHMETICOPERATION_H


#include "Operation.h"
#include "Token.h"

class ArithmeticOperation : public Operation {
public:
	ArithmeticOperation();

	void notify(ID id) override;
};


#endif //OOPPROJECT_ARITHMETICOPERATION_H
