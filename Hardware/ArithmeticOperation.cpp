#include "ArithmeticOperation.h"

ArithmeticOperation::ArithmeticOperation() : Operation(2) {
}

void ArithmeticOperation::notify(ID id) {
	process(); // create result
	send(); // send the result to target
}