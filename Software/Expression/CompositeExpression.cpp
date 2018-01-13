#include "CompositeExpression.h"
#include "ExpressionVisitor.h"
#include "../../Exceptions/IndexOutOfBoundsException.h"

CompositeExpression::CompositeExpression(size_t operandNum, Text name, Text opertaionType)
		: Expression(name), operands(operandNum, nullptr), operationType(opertaionType) {
}

CompositeExpression::~CompositeExpression() {
	for (auto &&operand : operands) {
		delete operand;
	}
}

void CompositeExpression::accept(ExpressionVisitor *visitor) {
	visitor->visitComposite(this);
}

const std::vector<Expression *> &CompositeExpression::getOperands() const {
	return operands;
}

void CompositeExpression::setOperand(size_t idx, Expression *operand) {
	if (idx >= 0 && idx < operands.size()) {
		operands[idx] = operand;
	} else {
		Text msg = "Index ";
		msg.append(std::to_string(idx));
		msg.append(" out of bounds");
		throw IndexOutOfBoundsException(msg);
	}
}

Expression *CompositeExpression::getOperand(size_t idx) {
	if (idx >= 0 && idx < operands.size()) {
		return operands[idx];
	} else {
		Text msg = "Index ";
		msg.append(std::to_string(idx));
		msg.append(" out of bounds");
		throw IndexOutOfBoundsException(msg);
	}
}

const Text &CompositeExpression::getOperationType() const {
	return operationType;
}

bool CompositeExpression::isComposite() {
	return true;
}
