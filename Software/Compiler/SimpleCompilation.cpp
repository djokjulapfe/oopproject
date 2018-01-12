#include "SimpleCompilation.h"

void SimpleCompilation::compile(Program *program) {
	Text programLine;
	while (program->nextCommand(programLine)) {
		auto expr = parseLine(programLine);
		outputExpression(expr);
	}
}

Expression *SimpleCompilation::parseLine(Text line) {
	return nullptr;
}
