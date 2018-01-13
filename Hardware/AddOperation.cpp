#include "AddOperation.h"
#include "Model.h"
#include "../Visitor/Visitor.h"

void AddOperation::process() {
	result = std::make_shared<Token>();
	result->setValue(inputPorts[0]->getValue() + inputPorts[1]->getValue());
}

void AddOperation::accept(Visitor *visitor) {
	visitor->visitAdd(this);
}

AddOperation::AddOperation(Text name) : ArithmeticOperation(name) {
	opTime = Model::Instance()->Ts;
}
