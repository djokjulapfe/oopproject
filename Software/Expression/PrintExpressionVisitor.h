#ifndef OOPPROJECT_PRINTEXPRESSIONVISITOR_H
#define OOPPROJECT_PRINTEXPRESSIONVISITOR_H


#include "ExpressionVisitor.h"

class PrintExpressionVisitor : public ExpressionVisitor{
public:
	void visitToken(TokenExpression *tokenExpression) override;

	void visitComposite(CompositeExpression *compositeExpression) override;

	const Text &getOutput() const;

private:
	Text output;
};


#endif //OOPPROJECT_PRINTEXPRESSIONVISITOR_H
