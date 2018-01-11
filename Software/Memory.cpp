#include "Memory.h"

Memory *Memory::Instance() {
	static Memory instance;
	return &instance;
}

void Memory::set(Text varName, double val) {
	mem[varName] = val;
}

double Memory::get(Text varName) {
	return mem[varName];
}
