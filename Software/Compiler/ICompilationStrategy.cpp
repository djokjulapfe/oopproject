#include <iostream>
#include <sstream>
#include "ICompilationStrategy.h"
#include "../Expression/PrintExpressionVisitor.h"
#include "Parser.h"

Text ICompilationStrategy::expressionToString(CompositeExpression *expression) {
	// creates Text from Expression
	if (expression == nullptr) {
		// TODO: throw exception
		std::cout << "No expression given in ICS::expressionToString\n";
		return "";
	}
	PrintExpressionVisitor visitor;
	visitor.visitComposite(expression);
	return visitor.getOutput();
}

size_t ICompilationStrategy::getPriority(Text operation) {
	if (operation == "=") return 1;
	if (operation == "+") return 2;
	if (operation == "*") return 3;
	if (operation == "^") return 4;
	return 0; // TODO: throw exception?
}

const Text &ICompilationStrategy::getCompiledCode() const {
	return compiledCode;
}
Text ICompilationStrategy::renameTemporaryVariables(Text code) {
	// TODO: remove dependecy on not having variables with name 't#*'
	if (code.empty()) {
		// TODO: throw exception?
		std::cout << "Empty string passed to renameTemporaryVariable\n";
		return "";
	}
	std::map<Text, Text> oldToNew;
	std::vector<Text> lines;
	std::stringstream ss(code);
	Text to;
	while (ss >> to) {
		if (to.length() > 1 && to[0] == 't' && Parser::isNumber(to[1])) {
			if (oldToNew.find(to) == oldToNew.end()) {
				Text tmpName = "t";
				tmpName.append(std::to_string(++tmpVarCount));
				oldToNew[to] = tmpName;
			}
		}
	}

	std::stringstream ss2(code);
	std::stringstream newss;

	while (ss2 >> to) {
		if (oldToNew.find(to) != oldToNew.end()) {
			newss << oldToNew[to] << " ";
		} else if (Parser::isSymbol(to[0])){
			newss << std::endl << ++lineCount << ": " << to << " ";
		} else {
			newss << to << " ";
		}
	}

	return newss.str();
}