#ifndef OOPPROJECT_TOKENEXPRESSION_H
#define OOPPROJECT_TOKENEXPRESSION_H


#include "Expression.h"

class TokenExpression : public Expression {

public:

	explicit TokenExpression(Text name);

	void accept(ExpressionVisitor *visitor) override;

	bool isComposite() override;

};


#endif //OOPPROJECT_TOKENEXPRESSION_H
