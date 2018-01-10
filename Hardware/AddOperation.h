#ifndef OOPPROJECT_ADDOPERATION_H
#define OOPPROJECT_ADDOPERATION_H


#include "ArithmeticOperation.h"

class AddOperation : public ArithmeticOperation {
public:
	void process() override;

	void accept(Visitor *visitor) override;

	void notify(ID id) override;
};


#endif //OOPPROJECT_ADDOPERATION_H
