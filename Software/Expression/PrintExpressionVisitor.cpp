#include <iostream>
#include "PrintExpressionVisitor.h"
#include "CompositeExpression.h"

void PrintExpressionVisitor::visitToken(TokenExpression *tokenExpression) {
}

void PrintExpressionVisitor::visitComposite(
		CompositeExpression *compositeExpression) {
	if (compositeExpression == nullptr) {
		// TODO: add exceptions
		std::cout << "nullptr passed to visitComposite\n";
		return;
	}
	for (auto &&operand : compositeExpression->getOperands()) {
		if (operand != nullptr) {
			operand->accept(this);
		} else {
			// TODO: add exceptions
			std::cout << "Operation has null operands\n";
			return;
		}
	}
	// TODO: append line numbers (labels)
	output.append("\n");
	output.append(compositeExpression->getOperationType());
	output.append(" ");
	output.append(compositeExpression->getName());
	output.append(" ");
	for (auto &&operand : compositeExpression->getOperands()) {
		output.append(operand->getName());
		output.append(" ");
	}
}

const Text &PrintExpressionVisitor::getOutput() const {
	return output;
}
