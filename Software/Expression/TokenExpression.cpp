#include "TokenExpression.h"
#include "ExpressionVisitor.h"
#include "Expression.h"

void TokenExpression::accept(ExpressionVisitor *visitor) {
	visitor->visit(this);
}

TokenExpression::TokenExpression(Text name) {
	this->name = name;
}
