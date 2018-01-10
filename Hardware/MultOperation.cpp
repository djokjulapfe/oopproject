#include "MultOperation.h"
#include "Model.h"

void MultOperation::process() {
	delete result;
	result = new Token;
	result->setValue(inputPorts[0]->getValue() * inputPorts[1]->getValue());
}

void MultOperation::accept(Visitor *visitor) {
	// TODO: implement
}

MultOperation::MultOperation() : ArithmeticOperation() {
	opTime = Model::Instance()->Tm;
}
