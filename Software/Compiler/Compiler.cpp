#include "Compiler.h"

Compiler::Compiler(ICompilation *strategy) : strategy(strategy) {
}

void Compiler::compile(Program *program) {
	strategy->compile(program);
}
