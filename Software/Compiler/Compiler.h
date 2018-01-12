#ifndef OOPPROJECT_COMPILER_H
#define OOPPROJECT_COMPILER_H


#include "../Program.h"
#include "ICompilation.h"

class Compiler {

public:

	explicit Compiler(ICompilation *strategy);

	virtual void compile(Program *program);

protected:

	ICompilation *strategy;

};


#endif //OOPPROJECT_COMPILER_H
