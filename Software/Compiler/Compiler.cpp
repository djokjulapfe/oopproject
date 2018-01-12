#include <iostream>
#include "Compiler.h"

Compiler::Compiler(ICompilationStrategy *strategy) : strategy(strategy) {
}

Compiler::~Compiler() {
	delete strategy;
}

void Compiler::compile(Program *program) {
	strategy->compile(program);
}
