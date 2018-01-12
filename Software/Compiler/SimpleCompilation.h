#ifndef OOPPROJECT_SIMPLECOMPILATION_H
#define OOPPROJECT_SIMPLECOMPILATION_H


#include "ICompilation.h"

class SimpleCompilation : public ICompilation {

public:

	void compile(Program *program) override;

protected:

	Expression *parseLine(Text line) override;
};


#endif //OOPPROJECT_SIMPLECOMPILATION_H
