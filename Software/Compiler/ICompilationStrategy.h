#ifndef OOPPROJECT_ICOMPILATION_H
#define OOPPROJECT_ICOMPILATION_H


#include "../Program.h"
#include "../Expression/Expression.h"

class ICompilationStrategy {

	/**
	 * @brief Strategy design pattern.
	 */

public:

	/**
	 * @brief Virtualisation of the desctructor for polymorphism
	 */
	virtual ~ICompilationStrategy() = default;

	/**
	 * @brief Convert a program to the intermediary form.
	 * @param program program to be translated
	 */
	virtual void compile(Program *program) = 0;

	const Text &getCompiledCode() const;

protected:

	/**
	 * @brief Returns the priority of an operation starting from 13
	 * @param operation name of the operation
	 * @return priority of an operation
	 */
	static size_t getPriority(Text operation);

	/**
	 * @brief Parses one line of code to an Expression tree.
	 * @param line to be parsed
	 * @return expression made from the input string
	 */
	virtual CompositeExpression* parseLine(Text line) = 0;

	/**
	 * @brief Converts an expression to the intermediary form.
	 * @param expression Expresion to be converted
	 * @returns intermediary form of the input expression
	 */
	virtual Text expressionToString(CompositeExpression *expression);

	/**
	 * @brief Makes the code user friendly by renaming variable names.
	 * @param code text that contains variables for renaming
	 * @return code with the renamed variables
	 */
	Text renameTemporaryVariables(Text code);

	// Temporary variable for storing number of intermediary variables
	size_t tmpVarCount;

	// Number of lines
	size_t lineCount;

	// List of concrete variable names used
	std::set<Text> varNames;

	// Text containing the intermediary form
	Text compiledCode;

};


#endif //OOPPROJECT_ICOMPILATION_H
