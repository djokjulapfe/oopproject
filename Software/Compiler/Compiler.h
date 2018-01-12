#ifndef OOPPROJECT_COMPILER_H
#define OOPPROJECT_COMPILER_H


#include "../Program.h"
#include "ICompilationStrategy.h"

class Compiler {

public:

	virtual ~Compiler();

	explicit Compiler(ICompilationStrategy *strategy);

	// prints the compiled program to a file
	// TODO: actually print it
	virtual void compile(Program *program);

protected:

	ICompilationStrategy *strategy;

};


#endif //OOPPROJECT_COMPILER_H
