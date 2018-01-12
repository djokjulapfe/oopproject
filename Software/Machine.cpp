#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Machine.h"
#include "../Hardware/Hardware.h"

Machine *Machine::Instance() {
	static Machine instance;
	return &instance;
}

Machine::Machine() {

}

void Machine::toExecute(ITimedOperation *operation) {
	auto position = std::find(waiting.begin(), waiting.end(), operation);
	waiting.erase(position);
	executing.insert(operation);
}

void Machine::toCompleted(ITimedOperation *operation) {
	auto iterator = std::find(executing.begin(), executing.end(), operation);
	executing.erase(iterator);
	completed.insert(operation);
	logs.insert(LogElement(operationToLabel[operation],
						   operation->startTime,
						   operation->startTime + operation->opTime));
}

void Machine::addOp(ITimedOperation *operation) {
	waiting.insert(operation);
}

void Machine::readProgram(Text imfPath) {

	Machine::Instance()->clear();
	Model::Instance()->clear();
	Scheduler::Instance()->clear();
	Memory::Instance()->clear();

	size_t programNameStart = imfPath.length();
	while (programNameStart >= 0 && imfPath[programNameStart] != '/') {
		programNameStart--;
	}
	programNameStart++;
	size_t programNameEnd = imfPath.length();
	while (programNameEnd >= 0 && imfPath[programNameEnd] != '.') {
		programNameEnd--;
	}
	programName = imfPath.substr(programNameStart,
								 programNameEnd - programNameStart);

	std::ifstream imfFile(imfPath);
	std::string line;
	if (imfFile.is_open()) {
		for (int i = 0; !imfFile.eof(); i++) {
			std::getline(imfFile, line);
			if (line[0] == '#') {
				i--;
				continue;
			}
			std::stringstream ss;
			ss << line;
			Text label, operationType, operationName;
			std::vector<Text> args;
			ss >> label >> operationType >> operationName;
			label = label.substr(0, label.length() - 1);
			do {
				Text tmp;
				ss >> tmp;
				args.push_back(tmp);
			} while (args.back().length());
			args.pop_back();
			if (operationType == "=") {
				new MemoryWriteOperation(operationName);
			} else if (operationType == "^") {
				new ExpOperation(operationName);
			} else if (operationType == "*") {
				new MultOperation(operationName);
			} else if (operationType == "+") {
				new AddOperation(operationName);
			}
			for (size_t j = 0; j < args.size(); ++j) {
				addArgument(j, operationName, args[j]);
			}
			operationToLabel[Model::operation(operationName)] =
					std::to_string(i + 1);
		}
		imfFile.close();
	} else {
		std::cout << "Error opening " << imfPath << std::endl;
	}
}

void Machine::addArgument(size_t idx, Text opTo, Text opFrom) {
	if (operationToLabel.find(Model::operation(opFrom)) !=
		operationToLabel.end()) {
		Model::operation(opFrom)->addTarget(idx, Model::operation(opTo));
	} else {
		Model::operation(opTo)->acceptToken(idx, std::make_shared<Token>(std::stoul(opFrom)));
	}
}

void Machine::execute() {
	Scheduler::Instance()->processNow();
}

void Machine::printLog() {
	std::cout << programName << ".log:\n";
	for (auto &&item : logs) {
		std::cout << item.label << ":\t"
				  << item.start << "/"
				  << item.end << std::endl;
	}
}

void Machine::exportLog(Text logDir) {

	std::ofstream logger(logDir);

	for (auto &&item : logs) {
		logger << item.label << ":\t"
			   << item.start << "/"
			   << item.end << std::endl;
	}

	logger.close();
}

void Machine::clear() {
	waiting.clear();
	executing.clear();
	completed.clear();
	operationToLabel.clear();
	logs.clear();
}

Machine::LogElement::LogElement(const Text &label, Time start, Time end)
		: label(label), start(start), end(end) {
}

bool Machine::LogElement::Compare::cmp(
		const Machine::LogElement &lhs,
		const Machine::LogElement &rhs) {
	if (lhs.start <= rhs.start) {
		if (lhs.start == rhs.start) {
			if (lhs.end <= rhs.end) {
				if (lhs.end == rhs.end) {
					return lhs.label < rhs.label;
				} else return true;
			} else return false;
		} else return true;
	} else return false;
}
