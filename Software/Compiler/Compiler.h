#ifndef OOPPROJECT_COMPILER_H
#define OOPPROJECT_COMPILER_H


#include "../Program.h"
#include "ICompilationStrategy.h"

class Compiler {

	/**
	 * @brief Class that helps with converting the code from a text file to the
	 * intermediary (.imf) file.
	 */

public:

	/**
	 * @brief Virtual destructor for polymorphism
	 */
	virtual ~Compiler();

	/**
	 * @brief Default constructor.
	 * @param strategy compilation strategy to be used for compiling.
	 */
	explicit Compiler(ICompilationStrategy *strategy);

	/**
	 * @brief Run's a compilation strategy.
	 * @param program program that should be translated
	 */
	virtual void compile(Program *program);

	virtual const Text &getCompiledCode();

	/**
	 * @brief Exports the compiled program to an imf file
	 */
	virtual void saveToImf();

protected:

	// Strategy denign pattern
	ICompilationStrategy *strategy;

	// Reference to a program that is being compiled
	Program *program;

};


#endif //OOPPROJECT_COMPILER_H
