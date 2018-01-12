#include <iostream>
#include "ICompilationStrategy.h"
#include "../Expression/PrintExpressionVisitor.h"

void ICompilationStrategy::outputExpression(CompositeExpression *expression) {
	if (expression == nullptr) {
		std::cout << "No expression given in ICS::outputExpression\n";
		return;
	}
	PrintExpressionVisitor visitor;
	visitor.visitComposite(expression);
	std::cout << visitor.getOutput() << std::endl;
}

size_t ICompilationStrategy::getPriority(Text operation) {
	if (operation == "=") return 1;
	if (operation == "+") return 2;
	if (operation == "*") return 3;
	if (operation == "^") return 4;
	return 0; // TODO: throw exception?
}
