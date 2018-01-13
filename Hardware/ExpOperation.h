#ifndef OOPPROJECT_EXPOPERATION_H
#define OOPPROJECT_EXPOPERATION_H


#include "ArithmeticOperation.h"

class ExpOperation : public ArithmeticOperation {

	/**
	 * @brief Concrete implementation of an exponentiaiton.
	 *
	 * result.value = inputPorts[0].value ^ inputPorts[1].value
	 */

public:

	void process() override;

	void accept(Visitor *visitor) override;

	ExpOperation(Text name = "Exponential Operation");

};


#endif //OOPPROJECT_EXPOPERATION_H
