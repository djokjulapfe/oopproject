#ifndef OOPPROJECT_ADDOPERATION_H
#define OOPPROJECT_ADDOPERATION_H


#include "ArithmeticOperation.h"

class AddOperation : public ArithmeticOperation {

public:

	void process() override;

	void accept(Visitor *visitor) override;

	AddOperation(Text name = "Add Operation");

};


#endif //OOPPROJECT_ADDOPERATION_H
