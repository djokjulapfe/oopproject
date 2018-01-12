#include <iostream>
#include "ICompilationStrategy.h"
#include "../Expression/PrintExpressionVisitor.h"

Text ICompilationStrategy::outputExpression(CompositeExpression *expression) {
	if (expression == nullptr) {
		// TODO: throw exception
		std::cout << "No expression given in ICS::outputExpression\n";
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
