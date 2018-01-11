#include "ExpOperation.h"
#include "Model.h"


void ExpOperation::process() {
	result = std::make_shared<Token>();
	result->setValue(inputPorts[0]->getValue() + inputPorts[1]->getValue());
}

void ExpOperation::accept(Visitor *visitor) {
	// TODO: implement this
}

ExpOperation::ExpOperation(Text text) : ArithmeticOperation(text) {
	opTime = Model::Instance()->Ts;
}
