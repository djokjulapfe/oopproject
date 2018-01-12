#ifndef OOPPROJECT_SIMPLECOMPILATION_H
#define OOPPROJECT_SIMPLECOMPILATION_H


#include "ICompilationStrategy.h"

class SimpleCompilation : public ICompilationStrategy {

public:

	void compile(Program *program) override;

protected:

	CompositeExpression *parseLine(Text line) override;

private:

	// can't use std::stack since it doesn't allow access of multiple top
	// elements
	std::vector<std::pair<Text, Expression *>> opStack;

	// helper methods
	std::deque<Text> split(Text text, char delimiter);

	bool isLetter(char c);

	bool isNumber(char c);

	bool isSymbol(char c);

	Text renameTemporaryVariables(Text code);

	size_t tmpVarCount, lineCount;

};


#endif //OOPPROJECT_SIMPLECOMPILATION_H