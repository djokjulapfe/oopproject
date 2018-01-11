#ifndef OOPPROJECT_EXPOPERATION_H
#define OOPPROJECT_EXPOPERATION_H


#include "ArithmeticOperation.h"

class ExpOperation : public ArithmeticOperation {

public:

	void process() override;

	void accept(Visitor *visitor) override;

	ExpOperation(Text name = "Exponential Operation");

};


#endif //OOPPROJECT_EXPOPERATION_H
