#include "AddOperation.h"
#include "Model.h"

void AddOperation::process() {
	result = std::make_shared<Token>();
	result->setValue(inputPorts[0]->getValue() + inputPorts[1]->getValue());
}

void AddOperation::accept(Visitor *visitor) {
	// TODO: implement this
}

AddOperation::AddOperation() : ArithmeticOperation() {
	opTime = Model::Instance()->Ts;
}
