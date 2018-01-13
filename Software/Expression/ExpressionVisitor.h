#ifndef OOPPROJECT_EXPRESSIONVISITOR_H
#define OOPPROJECT_EXPRESSIONVISITOR_H


#include "TokenExpression.h"

class ExpressionVisitor {

	/**
	 * @brief Visitor design pattern.
	 */

public:

	virtual void visitToken(TokenExpression *tokenExpression) = 0;

	virtual void visitComposite(CompositeExpression *compositeExpression) = 0;

};


#endif //OOPPROJECT_EXPRESSIONVISITOR_H
