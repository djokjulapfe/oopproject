#ifndef OOPPROJECT_ARITHMETICOPERATION_H
#define OOPPROJECT_ARITHMETICOPERATION_H


#include "Operation.h"
#include "Token.h"

class ArithmeticOperation : public Operation {

	/**
	 * @brief Intermediary class for operations with two input values
	 */

protected:

	ArithmeticOperation(Text name = "Arithmetic Operation");

};


#endif //OOPPROJECT_ARITHMETICOPERATION_H
