#ifndef OOPPROJECT_EXPRESSION_H
#define OOPPROJECT_EXPRESSION_H

#include "../../Utils/utils.h"

class ExpressionVisitor;
class CompositeExpression;

class Expression {

public:

	Expression(const Text &name);

	virtual ~Expression();

	virtual void accept(ExpressionVisitor *visitor) = 0;

	const Text &getName() const;

	virtual bool isComposite() = 0;

protected:

	Text name;

};


#endif //OOPPROJECT_EXPRESSION_H
