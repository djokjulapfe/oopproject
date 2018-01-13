#ifndef OOPPROJECT_ADVANCEDCOMPILATION_H
#define OOPPROJECT_ADVANCEDCOMPILATION_H


#include "ICompilationStrategy.h"

class AdvancedCompilation : public ICompilationStrategy {

public:

	void compile(Program *program) override;

protected:

	CompositeExpression *parseLine(Text line) override;

private:

	// TODO: this is left from SimpleCompilation
	std::vector<std::pair<Text, Expression *>> opStack;

	// rearranges the variables for minimal MemoryWrite
	virtual std::vector<Text> prepareProgram(Program *program);

	// helper methods
	virtual std::set<Text> dependentVariables(std::vector<Text> Tokens);

};


#endif //OOPPROJECT_ADVANCEDCOMPILATION_H
