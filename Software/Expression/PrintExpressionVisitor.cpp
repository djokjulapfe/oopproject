#include "PrintExpressionVisitor.h"
#include "CompositeExpression.h"

void PrintExpressionVisitor::visit(TokenExpression *tokenExpression) {
}

void PrintExpressionVisitor::visit(CompositeExpression *compositeExpression) {
	for (auto &&operand : compositeExpression->getOperands()) {
		operand->accept(this);
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
