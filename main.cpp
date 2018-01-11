#include <iostream>
#include "Hardware/Operation.h"
#include "Hardware/AddOperation.h"
#include "SimulationEngine/SimulationEngine.h"
#include "Hardware/MultOperation.h"
#include "Hardware/MemoryWriteOperation.h"
#include "Hardware/Model.h"

void test1() {
	Operation *addop = new AddOperation("addop");
	Model::operation("addop")->acceptToken(0, std::make_shared<Token>(3));
	Model::operation("addop")->acceptToken(1, std::make_shared<Token>(2));
	Model::operation("addop")->notify(0);
	std::cout << Model::operation("addop")->result->value << std::endl;

	Model::Instance()->clear();
	Scheduler::Instance()->clear();

	Operation *add1 = new AddOperation("add1");
	Operation *add2 = new AddOperation("add2");
	Operation *add3 = new AddOperation("add3");
	add1->addTarget(0, add3);
	add2->addTarget(1, add3);
	add1->acceptToken(0, std::make_shared<Token>(1, "op11"));
	add1->acceptToken(1, std::make_shared<Token>(2, "op12"));
	add1->notify(0);
	add2->acceptToken(0, std::make_shared<Token>(3, "op21"));
	add2->acceptToken(1, std::make_shared<Token>(4, "op22"));
	add2->notify(0);
	add3->notify(0);
	if (add3->result) std::cout << add3->result->value << std::endl;
	else std::cout << "Value not yet calculated\n";

	Model::Instance()->clear();
	Scheduler::Instance()->clear();

	add1 = new AddOperation;
	add2 = new MultOperation;
	add3 = new AddOperation;
	Operation *add4 = new MultOperation;
	Operation *memwr = new MemoryWriteOperation;

	add1->setName("A1");
	add2->setName("M1");
	add3->setName("A2");
	add4->setName("M2");
	memwr->setName("memwr1");

	add1->id = 1;
	add2->id = 2;
	add3->id = 3;
	add4->id = 4;
	memwr->id = 73;

	add1->addTarget(0, add3);
	add2->addTarget(1, add3);
	add2->addTarget(0, add4);
	memwr->addTarget(0, add1);

	memwr->acceptToken(0, std::make_shared<Token>(1, "op11"));
	add1->acceptToken(1, std::make_shared<Token>(2, "op12"));
	add2->acceptToken(0, std::make_shared<Token>(3, "op21"));
	add2->acceptToken(1, std::make_shared<Token>(4, "op22"));
	add4->acceptToken(1, std::make_shared<Token>(-5, "op32"));
	Scheduler::Instance()->processNow();
	if (add3->result) std::cout << add3->result->value << std::endl;
	else std::cout << "Value not yet calculated\n";
	if (add4->result) std::cout << add4->result->value << std::endl;
	else std::cout << "Value not yet calculated\n";

	Model::Instance()->clear();
	Scheduler::Instance()->clear();
}

int main() {
	test1();
	return 0;
}