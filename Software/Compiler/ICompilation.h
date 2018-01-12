#ifndef OOPPROJECT_ICOMPILATION_H
#define OOPPROJECT_ICOMPILATION_H


#include "../Program.h"
#include "../Expression/Expression.h"

class ICompilation {

public:

	virtual void compile(Program *program) = 0;

protected:

	virtual Expression* parseLine(Text line) = 0;

	virtual void outputExpression(Expression *expression);

};


#endif //OOPPROJECT_ICOMPILATION_H
