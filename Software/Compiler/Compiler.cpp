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
	Text imfDir = program->getPath();
	size_t it = imfDir.length() - 1;
	while (imfDir[it] != '.') {
		imfDir.pop_back();
		it--;
	}
	imfDir.append("imf");
	std::ofstream imfFile(imfDir);
	imfFile << getCompiledCode();
	imfFile.close();
}
