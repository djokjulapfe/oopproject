#ifndef OOPPROJECT_ADDOPERATION_H
#define OOPPROJECT_ADDOPERATION_H


#include "ArithmeticOperation.h"

class AddOperation : public ArithmeticOperation {

	/**
	 * @brief Concrete implementation of an addition.
	 *
	 * result.value = inputPorts[0].value + inputPorts[1].value
	 */

public:

	void process() override;

	void accept(Visitor *visitor) override;

	explicit AddOperation(Text name = "Add Operation");

};


#endif //OOPPROJECT_ADDOPERATION_H
