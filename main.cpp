#include <iostream>
#include "Hardware/Operation.h"
#include "Hardware/AddOperation.h"
#include "SimulationEngine/SimulationEngine.h"
#include "Hardware/MultOperation.h"

void test1() {
//	Operation *addop = new AddOperation;
//	addop->acceptToken(0, new Token(3));
//	addop->acceptToken(1, new Token(2));
//	addop->notify(0);
//	std::cout << addop->result->value << std::endl;
//	delete addop;
//
//	Operation *add1 = new AddOperation;
//	Operation *add2 = new AddOperation;
//	Operation *add3 = new AddOperation;
//	Operation *add4 = new AddOperation;
//	add1->addTarget(0, add3);
//	add2->addTarget(1, add3);
//	add1->acceptToken(0, new Token(1, "op11"));
//	add1->acceptToken(1, new Token(2, "op12"));
//	add1->notify(0);
//	add2->acceptToken(0, new Token(3, "op21"));
//	add2->acceptToken(1, new Token(4, "op22"));
//	add2->notify(0);
//	add3->notify(0);
//	if (add3->result) std::cout << add3->result->value << std::endl;
//	else std::cout << "Value not yet calculated\n";
//	delete add1;
//	delete add2;
//	delete add3;

	Scheduler::Instance()->clear();

	Operation *add1 = new AddOperation;
	Operation *add2 = new AddOperation;
	Operation *add3 = new AddOperation;
	Operation *add4 = new AddOperation;
	add1->setName("Add1");
	add2->setName("Add2");
	add3->setName("Add3");
	add4->setName("Add4");
	add1->id = 1;
	add2->id = 2;
	add3->id = 3;
	add4->id = 4;
	add1->addTarget(0, add3);
	add2->addTarget(1, add3);
	add2->addTarget(0, add4);
	add1->acceptToken(0, new Token(1, "op11"));
	add1->acceptToken(1, new Token(2, "op12"));
	add2->acceptToken(0, new Token(3, "op21"));
	add2->acceptToken(1, new Token(4, "op22"));
	add4->acceptToken(1, new Token(-5, "op32"));
	//Event::create(add1, add1->opTime);
	//Event::create(add2, add1->opTime);
	Scheduler::Instance()->processNow();
	if (add3->result) std::cout << add3->result->value << std::endl;
	else std::cout << "Value not yet calculated\n";
	if (add4->result) std::cout << add4->result->value << std::endl;
	else std::cout << "Value not yet calculated\n";

	delete add1;
	delete add2;
	delete add3;
	delete add4;
}

int main() {
	test1();
	return 0;
}