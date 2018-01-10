#include "AddOperation.h"

void AddOperation::process() {
	delete result;
	result = new Token;
	result->setValue(inputPorts[0]->getValue() + inputPorts[1]->getValue());
}

void AddOperation::accept(Visitor *visitor) {

}

void AddOperation::notify(ID id) {

}
