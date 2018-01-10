#include "Operation.h"
#include "Token.h"

ID Operation::maxId = 0;

const Text &Operation::getName() const {
	return name;
}

void Operation::setName(const Text &name) {
	Operation::name = name;
}

const Text &Operation::getDescription() const {
	return description;
}

void Operation::setDescription(const Text &description) {
	Operation::description = description;
}

void Operation::acceptToken(size_t idx, Token *token) {
	delete inputPorts[idx];
	inputPorts[idx] = token;
	if (allTokensAccepted()) {
		process();
	}
}

void Operation::send() {
	for (int i = 0; i < inputPorts.size(); ++i) {
		delete inputPorts[i];
	}
	target->acceptToken(targetIdx, result);
}

bool Operation::allTokensAccepted() {
	for (auto &&item : inputPorts) {
		if (item == nullptr) return false;
	}
	return true;
}

Operation::Operation(size_t inputPortSize)
		: inputPorts(inputPortSize, nullptr) {
	id = maxId;
	maxId++;
	name = "Unnamed Operation";
}
