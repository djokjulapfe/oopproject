#include <iostream>
#include "Hardware/Operation.h"
#include "Hardware/AddOperation.h"
#include "SimulationEngine/SimulationEngine.h"
#include "Hardware/MultOperation.h"
#include "Hardware/MemoryWriteOperation.h"
#include "Hardware/ExpOperation.h"
#include "Software/Machine.h"

void initNewTest() {

	Machine::Instance()->clear();
	Model::Instance()->clear();
	Scheduler::Instance()->clear();
	Memory::Instance()->clear();

}

void test1() {
	new AddOperation("addop");
	Model::operation("addop")->acceptToken(0, std::make_shared<Token>(3));
	Model::operation("addop")->acceptToken(1, std::make_shared<Token>(2));
	Model::operation("addop")->notify(0);
	std::cout << Model::operation("addop")->result->value << std::endl;

	initNewTest();

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

	initNewTest();

	Operation *memwr = new MemoryWriteOperation;
	add1 = new AddOperation;
	add2 = new MultOperation;
	add3 = new AddOperation;
	Operation *add4 = new MultOperation;

	memwr->setName("memwr1");
	add1->setName("A1");
	add2->setName("M1");
	add3->setName("A2");
	add4->setName("M2");

	memwr->id = 73;
	add1->id = 1;
	add2->id = 2;
	add3->id = 3;
	add4->id = 4;

	memwr->addTarget(0, add1);
	add1->addTarget(0, add3);
	add2->addTarget(1, add3);
	add2->addTarget(0, add4);

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
}

void test2() {
	// Testing the code given in "prilog" section

	initNewTest();


	//1
	new MemoryWriteOperation("x"); // = 2
	Model::operation("x")->acceptToken(0, std::make_shared<Token>(2, "x"));

	//2
	new MemoryWriteOperation("y"); // = 3
	Model::operation("y")->acceptToken(0, std::make_shared<Token>(3, "y"));

	//3
	new ExpOperation("t1"); // = x ^ 3
	Model::operation("x")->addTarget(0, Model::operation("t1"));
	Model::operation("t1")->acceptToken(1, std::make_shared<Token>(3));

	//4
	new MultOperation("t2"); // = 2 * t1
	Model::operation("t2")->acceptToken(0, std::make_shared<Token>(2));
	Model::operation("t1")->addTarget(1, Model::operation("t2"));

	//5
	new ExpOperation("t3"); // = x ^ 5
	Model::operation("x")->addTarget(0, Model::operation("t3"));
	Model::operation("t3")->acceptToken(1, std::make_shared<Token>(5));

	//6
	new ExpOperation("t4"); // = y ^ 3
	Model::operation("y")->addTarget(0, Model::operation("t4"));
	Model::operation("t4")->acceptToken(1, std::make_shared<Token>(3));

	//7
	new MultOperation("t5"); // = t3 * t4
	Model::operation("t3")->addTarget(0, Model::operation("t5"));
	Model::operation("t4")->addTarget(1, Model::operation("t5"));

	//8
	new AddOperation("t6"); // = t2 + t5
	Model::operation("t2")->addTarget(0, Model::operation("t6"));
	Model::operation("t5")->addTarget(1, Model::operation("t6"));

	//9
	new AddOperation("t7"); // = t6 + 5
	Model::operation("t6")->addTarget(0, Model::operation("t7"));
	Model::operation("t7")->acceptToken(1, std::make_shared<Token>(5));

	//10
	new MemoryWriteOperation("z"); // = t7
	Model::operation("t7")->addTarget(0, Model::operation("z"));

	//11
	new MultOperation("t8"); // = x * x
	Model::operation("x")->addTarget(0, Model::operation("t8"));
	Model::operation("x")->addTarget(1, Model::operation("t8"));

	//12
	new AddOperation("t9"); // = t8 + 2
	Model::operation("t8")->addTarget(0, Model::operation("t9"));
	Model::operation("t9")->acceptToken(1, std::make_shared<Token>(2));

	//13
	new MemoryWriteOperation("d"); // = d t9
	Model::operation("t9")->addTarget(0, Model::operation("d"));

	Scheduler::Instance()->processNow();

	Memory::Instance()->printMemory();
}

void test3() {
	initNewTest();
	Machine::Instance()->readProgram("../programs/prilogProgram.imf");
	Machine::Instance()->execute();
	Machine::Instance()->printLog();
	Memory::Instance()->printMemory();
}

int main() {
	std::cout << "\n------------TEST1------------\n\n";
	test1();
	std::cout << "\n------------TEST2------------\n\n";
	test2();
	std::cout << "\n------------TEST3------------\n\n";
	test3();
//	int x = 2;
//	int y = 3;
//	std::cout << "OUT OF TESTS: " << x*x*x*(2+y*y*y*x*x) + 5<< std::endl;
	return 0;
}