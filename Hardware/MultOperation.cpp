#include "MultOperation.h"
#include "Model.h"
#include "../Visitor/Visitor.h"

void MultOperation::process() {
	result = std::make_shared<Token>();
	result->setValue(inputPorts[0]->getValue() * inputPorts[1]->getValue());
}

void MultOperation::accept(Visitor *visitor) {
	visitor->visitMult(this);
}

MultOperation::MultOperation(Text name) : ArithmeticOperation(name) {
	opTime = Model::Instance()->Tm;
}
