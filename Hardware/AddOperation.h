#ifndef OOPPROJECT_ADDOPERATION_H
#define OOPPROJECT_ADDOPERATION_H


#include "ArithmeticOperation.h"

class AddOperation : public ArithmeticOperation {
public:
	AddOperation();

	void process() override;

	void accept(Visitor *visitor) override;
};


#endif //OOPPROJECT_ADDOPERATION_H
