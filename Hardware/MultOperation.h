#ifndef OOPPROJECT_MULTOPERATION_H
#define OOPPROJECT_MULTOPERATION_H


#include "ArithmeticOperation.h"

class MultOperation : public ArithmeticOperation {

public:

	void process() override;

	void accept(Visitor *visitor) override;

	MultOperation(Text name = "Multiply Operation");

};


#endif //OOPPROJECT_MULTOPERATION_H
