#ifndef OOPPROJECT_ICOMPILATION_H
#define OOPPROJECT_ICOMPILATION_H


#include "../Program.h"
#include "../Expression/Expression.h"

class ICompilationStrategy {

public:

	virtual ~ICompilationStrategy() = default;

	virtual void compile(Program *program) = 0;

	const Text &getCompiledCode() const;

protected:

	virtual CompositeExpression* parseLine(Text line) = 0;

	virtual Text expressionToString(CompositeExpression *expression);

	Text renameTemporaryVariables(Text code);

	size_t tmpVarCount, lineCount;

	std::set<Text> varNames;

public:

	static size_t getPriority(Text operation);

	Text compiledCode;

};


#endif //OOPPROJECT_ICOMPILATION_H
