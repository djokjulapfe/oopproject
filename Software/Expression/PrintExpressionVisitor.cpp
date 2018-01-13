#include <iostream>
#include "PrintExpressionVisitor.h"
#include "CompositeExpression.h"
#include "../../Exceptions/VisitorException.h"

void PrintExpressionVisitor::visitToken(TokenExpression *tokenExpression) {
}

void PrintExpressionVisitor::visitComposite(
		CompositeExpression *compositeExpression) {

	// check if an expression is passed
	if (compositeExpression == nullptr) {
		Text msg = "nullptr passed to visitComposite";
		throw VisitorException(msg);
	}

	// visit all of the expression's operands
	for (auto &&operand : compositeExpression->getOperands()) {
		if (operand != nullptr) {
			operand->accept(this);
		} else {
			Text msg = "Expression ";
			msg.append(compositeExpression->getName());
			msg.append(" has a null operand");
			throw VisitorException(msg);
		}
	}

	// output the expression
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
