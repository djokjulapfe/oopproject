#include "MemoryWriteOperation.h"
#include "Token.h"
#include "../SimulationEngine/Event.h"
#include "../Visitor/Visitor.h"

void MemoryWriteOperation::process() {
	result = std::make_shared<Token>();
	result->setValue(inputPorts[0]->value);
	Memory::Instance()->set(getName(), result->value);
	if (owningThread && !owningThread->ops.empty()) {
		Event::create(owningThread->ops.front(), Model::Instance()->Mw);
		owningThread->ops.pop();
	}
}

void MemoryWriteOperation::accept(Visitor *visitor) {
	visitor->visitMemoryWrite(this);
}

MemoryWriteOperation::MemoryWriteOperation(Text name) : MemoryOperation(name) {
	opTime = Model::Instance()->Mw;
}

void MemoryWriteOperation::acceptToken(
		size_t idx,
		std::shared_ptr<Token> token) {
	inputPorts[idx] = token;
	if (allTokensAccepted()) {
		if (Memory::Instance()->writeFreeIn() == 0) {
			Event::create(this, opTime);
		}
		Memory::Instance()->addWriter(this);
	}
}


