#ifndef OOPPROJECT_COMPOSITEEXPRESSION_H
#define OOPPROJECT_COMPOSITEEXPRESSION_H


#include "Expression.h"

class CompositeExpression : public Expression {

public:

	explicit CompositeExpression(size_t operandNum, Text operationType);

	virtual ~CompositeExpression();

	void accept(ExpressionVisitor *visitor) override;

	void setOperand(size_t idx, Expression *operand);

	Expression *getOperand(size_t idx);

	const std::vector<Expression *> &getOperands() const;

	const Text &getOperationType() const;

protected:

	std::vector<Expression*> operands;

	Text operationType;

};


#endif //OOPPROJECT_COMPOSITEEXPRESSION_H
