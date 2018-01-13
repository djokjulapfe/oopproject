#ifndef OOPPROJECT_ADVANCEDCOMPILATION_H
#define OOPPROJECT_ADVANCEDCOMPILATION_H


#include "ICompilationStrategy.h"

class AdvancedCompilation : public ICompilationStrategy {

	/**
	 * @brief Advanced Compilation that minimizes waiting on memory writes and
	 * minimizes height of single-operation trees
	 */

public:

	void compile(Program *program) override;

protected:

	CompositeExpression *parseLine(Text line) override;

private:

	/**
	 * @brief Rearranges the variables for minimal memory write waiting.
	 * @param program that should be optimized
	 * @return list of code lines in the optimized order
	 */
	virtual std::vector<Text> prepareProgram(Program *program);

	// helper methods
	/**
	 * @brief Finds the variable an expression depends on.
	 * @param Tokens list of possible dependencies
	 * @return sed of dependencies
	 */
	virtual std::set<Text> dependentVariables(std::vector<Text> Tokens);

	/**
	 * @brief Recursive call for creating the expression tree.
	 * @param subLine expression split to tokens
	 * @param token splitting criteria
	 * @return expression tree
	 */
	virtual Expression * subDivide(std::vector<Text> subLine, Text token);

	/**
	 * @brief Next operation in the order of operations
	 * @param token an operation
	 * @return next operation
	 */
	virtual Text nextToken(Text token);

};


#endif //OOPPROJECT_ADVANCEDCOMPILATION_H
