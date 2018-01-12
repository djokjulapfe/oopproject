#ifndef OOPPROJECT_ICOMPILATION_H
#define OOPPROJECT_ICOMPILATION_H


#include "../Program.h"
#include "../Expression/Expression.h"

class ICompilationStrategy {

public:

	virtual ~ICompilationStrategy() = default;

	virtual void compile(Program *program) = 0;

protected:

	virtual CompositeExpression* parseLine(Text line) = 0;

	virtual void outputExpression(CompositeExpression *expression);

public:

	static size_t getPriority(Text operation);

};


#endif //OOPPROJECT_ICOMPILATION_H
