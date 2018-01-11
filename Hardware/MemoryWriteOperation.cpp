#include "MemoryWriteOperation.h"
#include "Token.h"
#include "Model.h"

void MemoryWriteOperation::process() {
	result = std::make_shared<Token>();
	result->setValue(inputPorts[0]->value);
}

void MemoryWriteOperation::accept(Visitor *visitor) {
	// TODO: implement this
}

MemoryWriteOperation::MemoryWriteOperation(Text name) : MemoryOperation(name) {
	opTime = Model::Instance()->Mw;
}


