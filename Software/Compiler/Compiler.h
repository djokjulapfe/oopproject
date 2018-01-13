#ifndef OOPPROJECT_COMPILER_H
#define OOPPROJECT_COMPILER_H


#include "../Program.h"
#include "ICompilationStrategy.h"

class Compiler {

public:

	virtual ~Compiler();

	explicit Compiler(ICompilationStrategy *strategy);

	virtual void compile(Program *program);

	virtual const Text &getCompiledCode();

	virtual void saveToImf();

protected:

	ICompilationStrategy *strategy;

	Program *program;

};


#endif //OOPPROJECT_COMPILER_H
