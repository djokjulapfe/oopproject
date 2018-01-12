#ifndef OOPPROJECT_EXPRESSIONVISITOR_H
#define OOPPROJECT_EXPRESSIONVISITOR_H


#include "TokenExpression.h"

class ExpressionVisitor {

public:

	virtual void visit(TokenExpression *tokenExpression) = 0;

	virtual void visit(CompositeExpression *compositeExpression) = 0;

};


#endif //OOPPROJECT_EXPRESSIONVISITOR_H
