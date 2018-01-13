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

	// moves an operation from one set to another
	auto position = std::find(waiting.begin(), waiting.end(), operation);
	waiting.erase(position);
	executing.insert(operation);

}

void Machine::toCompleted(ITimedOperation *operation) {

	// moves an operation from one set to another
	auto iterator = std::find(executing.begin(), executing.end(), operation);
	executing.erase(iterator);
	completed.insert(operation);

	// updates the logs
	logs.insert(LogElement(operationToLabel[operation],
						   operation->startTime,
						   operation->startTime + operation->opTime));

	// sends the tokens to the next operation
	operation->send();

}

void Machine::addOp(ITimedOperation *operation) {
	waiting.insert(operation);
}

void Machine::readProgram(Text imfPath) {

	// prepare for the program
	Machine::Instance()->clear();
	Model::Instance()->clear();
	Scheduler::Instance()->clear();
	Memory::Instance()->clear();

	// find the program name
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

	// loop through the lines in the file
	std::ifstream imfFile(imfPath);
	std::string line;
	if (imfFile.is_open()) {
		for (int i = 0; !imfFile.eof(); i++) {

			// read one line
			std::getline(imfFile, line);

			// skip it if it is a comment
			if (line[0] == '#') {
				i--;
				continue;
			}

			// load the first three tokens
			std::stringstream ss;
			ss << line;
			Text label, operationType, operationName;
			ss >> label >> operationType >> operationName;

			// load the rest of the tokens
			std::vector<Text> args;
			label = label.substr(0, label.length() - 1);
			do {
				Text tmp;
				ss >> tmp;
				args.push_back(tmp);
			} while (args.back().length());

			// remove the blank token at the end
			args.pop_back();

			// create an operation based on it's type
			if (operationType == "=") {
				new MemoryWriteOperation(operationName);
			} else if (operationType == "^") {
				new ExpOperation(operationName);
			} else if (operationType == "*") {
				new MultOperation(operationName);
			} else if (operationType == "+") {
				new AddOperation(operationName);
			}

			// add all the arguments
			for (size_t j = 0; j < args.size(); ++j) {
				addArgument(j, operationName, args[j]);
			}

			// save the operation - label pair
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

		// if the opFrom is an operation add the target
		Model::operation(opFrom)->addTarget(idx, Model::operation(opTo));

	} else {

		// if the opFrom is a variable or a constant add a token
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

void Machine::exportLog(Text logPath) {

	std::ofstream logger(logPath);

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

	// first checks the start, then the and, and the label at the end
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
