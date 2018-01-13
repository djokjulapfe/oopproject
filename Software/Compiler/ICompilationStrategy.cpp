#include <iostream>
#include <sstream>
#include "ICompilationStrategy.h"
#include "../Expression/PrintExpressionVisitor.h"
#include "Parser.h"
#include "../../Exceptions/BadExpressionException.h"

Text ICompilationStrategy::expressionToString(CompositeExpression *expression) {

	// creates Text from Expression
	if (expression == nullptr) {
		throw BadExpressionException("No expression given");
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
	return 0;

}

const Text &ICompilationStrategy::getCompiledCode() const {
	return compiledCode;
}
Text ICompilationStrategy::renameTemporaryVariables(Text code) {

	// TODO: remove dependency on not having variables with name 't#*'
	if (code.empty()) {
		throw BadExpressionException("No code given for renaming");
	}

	std::map<Text, Text> oldToNew;
	std::vector<Text> lines;
	std::stringstream ss(code);
	Text to;

	// generate oldToNew mapping
	while (ss >> to) {

		// if to is a temporary varaible
		if (to.length() > 1 && to[0] == 't' && Parser::isNumber(to[1])) {

			// if the variable wasn't
			if (oldToNew.find(to) == oldToNew.end()) {

				Text tmpName = "t";
				tmpName.append(std::to_string(++tmpVarCount));
				oldToNew[to] = tmpName;

			}

		}

	}

	std::stringstream ss2(code);
	std::stringstream newss;

	// change the names of the variables
	while (ss2 >> to) {

		if (oldToNew.find(to) != oldToNew.end()) {

			// if the variable should be changed, change it
			newss << oldToNew[to] << " ";

		} else if (Parser::isSymbol(to[0])){

			// add label if it is the token is a symbol
			newss << std::endl << ++lineCount << ": " << to << " ";

		} else {

			newss << to << " ";

		}
	}

	// return the string
	return newss.str();

}