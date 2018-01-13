#ifndef OOPPROJECT_SIMPLECOMPILATION_H
#define OOPPROJECT_SIMPLECOMPILATION_H


#include "ICompilationStrategy.h"

class SimpleCompilation : public ICompilationStrategy {

	/**
	 * @brief Simple compilation algorithm that reads the string character by
	 * character and creates an straightforward expression tree
	 */

public:

	void compile(Program *program) override;

protected:

	CompositeExpression *parseLine(Text line) override;

private:

	// Used for creating the expression tree in the operation stack
	std::vector<std::pair<Text, Expression *>> opStack;

};


#endif //OOPPROJECT_SIMPLECOMPILATION_H
