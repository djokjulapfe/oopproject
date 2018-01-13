#include "MemoryReadOperation.h"
#include "Token.h"
#include "../SimulationEngine/Event.h"
#include "../Visitor/Visitor.h"

void MemoryReadOperation::process() {
	result = std::make_shared<Token>();
	result->setValue(inputPorts[0]->value);
	auto value = Memory::Instance()->get(getName());
	if (owningThread && !owningThread->ops.empty()) {
		Event::create(owningThread->ops.front(), opTime);
		owningThread->ops.pop();
	}
}

void MemoryReadOperation::accept(Visitor *visitor) {
	visitor->visitMemoryRead(this);
}

MemoryReadOperation::MemoryReadOperation(Text name) : MemoryOperation(name) {
	opTime = Model::Instance()->Mr;
}

void MemoryReadOperation::acceptToken(
		size_t idx,
		std::shared_ptr<Token> token) {
	inputPorts[idx] = token;
	if (allTokensAccepted()) {
		if (Memory::Instance()->readFreeIn() == 0) {
			Event::create(this, opTime);
		}
		Memory::Instance()->addReader(this);
	}
}
