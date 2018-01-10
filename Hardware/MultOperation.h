#ifndef OOPPROJECT_MULTOPERATION_H
#define OOPPROJECT_MULTOPERATION_H


#include "ArithmeticOperation.h"

class MultOperation : public ArithmeticOperation {
public:
	MultOperation();

	void process() override;

	void accept(Visitor *visitor) override;
};


#endif //OOPPROJECT_MULTOPERATION_H
