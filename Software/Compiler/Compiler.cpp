#include <iostream>
#include "Compiler.h"

Compiler::Compiler(ICompilationStrategy *strategy) : strategy(strategy) {
}

Compiler::~Compiler() {
	delete strategy;
}

void Compiler::compile(Program *program) {
	this->program = program;
	strategy->compile(program);
}

const Text &Compiler::getCompiledCode() {
	return strategy->getCompiledCode();
}

void Compiler::saveToImf() {

	Text imfDir = program->getImfPath();
	std::ofstream imfFile(imfDir);
	imfFile << getCompiledCode();
	imfFile.close();

}
