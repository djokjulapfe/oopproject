#include <iostream>
#include "Hardware/Operation.h"
#include "Hardware/AddOperation.h"

void test1() {
	Operation *addop = new AddOperation;
	addop->acceptToken(0, new Token(3));
	addop->acceptToken(1, new Token(2));
	std::cout << addop->result->value;
}

int main() {
	test1();
	return 0;
}