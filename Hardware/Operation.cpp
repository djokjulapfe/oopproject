#include <iostream>
#include <utility>
#include "Operation.h"
#include "Token.h"
#include "../SimulationEngine/Event.h"

Operation::~Operation() {
	for (auto &&target : targets) {
		target.second->inputPorts[target.first] = nullptr;
	}
}

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

void Operation::acceptToken(size_t idx, std::shared_ptr<Token> token) {
	inputPorts[idx] = token;
	if (allTokensAccepted()) {
		Event::create(this, opTime);
	}
}

void Operation::send() {

	for (int i = 0; i < inputPorts.size(); ++i) {
		inputPorts[i] = nullptr;
	}

	for (auto &&target : targets) {
		if (target.second) {
			target.second->acceptToken(target.first, result);
		}
	}

}

bool Operation::allTokensAccepted() {
	for (auto &&item : inputPorts) {
		if (item == nullptr) return false;
	}
	return true;
}

void Operation::addTarget(size_t idx, Operation *operation) {
	targets.emplace_back(idx, operation);
}

Operation::Operation(size_t inputPortSize)
		: inputPorts(inputPortSize, nullptr) {
	id = maxId;
	maxId++;
	name = "Unnamed Operation";
	result = nullptr;
}
