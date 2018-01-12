#include "CompositeExpression.h"
#include "ExpressionVisitor.h"

CompositeExpression::CompositeExpression(size_t operandNum, Text opertaionType)
		: operands(operandNum, nullptr), operationType(opertaionType) {
}

CompositeExpression::~CompositeExpression() {
	for (auto &&operand : operands) {
		delete operand;
	}
}

void CompositeExpression::accept(ExpressionVisitor *visitor) {
	visitor->visit(this);
}

const std::vector<Expression *> &CompositeExpression::getOperands() const {
	return operands;
}

void CompositeExpression::setOperand(size_t idx, Expression *operand) {
	// TODO: check if idx out of bounds
	operands[idx] = operand;
}

Expression *CompositeExpression::getOperand(size_t idx) {
	// TODO: check if idx out of bounds
	return operands[idx];
}

const Text &CompositeExpression::getOperationType() const {
	return operationType;
}
