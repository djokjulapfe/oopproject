#include "ExpOperation.h"
#include "Model.h"
#include "../Visitor/Visitor.h"

void ExpOperation::process() {
	result = std::make_shared<Token>();
	result->setValue(
			std::pow(inputPorts[0]->getValue(), inputPorts[1]->getValue()));
}

void ExpOperation::accept(Visitor *visitor) {
	visitor->visitExp(this);
}

ExpOperation::ExpOperation(Text text) : ArithmeticOperation(text) {
	opTime = Model::Instance()->Te;
}
