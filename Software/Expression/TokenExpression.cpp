#include "TokenExpression.h"
#include "ExpressionVisitor.h"
#include "Expression.h"

void TokenExpression::accept(ExpressionVisitor *visitor) {
	visitor->visitToken(this);
}

TokenExpression::TokenExpression(Text name) : Expression(name) {
}
