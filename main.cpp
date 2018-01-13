#include <iostream>
#include <sstream>
#include "Hardware/Operation.h"
#include "Hardware/AddOperation.h"
#include "SimulationEngine/SimulationEngine.h"
#include "Hardware/Hardware.h"
#include "Software/Machine.h"
#include "Software/Expression/CompositeExpression.h"
#include "Software/Expression/BinaryOperationExpression.h"
#include "Software/Expression/TokenExpression.h"
#include "Software/Expression/PrintExpressionVisitor.h"
#include "Software/Program.h"
#include "Software/Compiler/Compiler.h"
#include "Software/Compiler/SimpleCompilation.h"
#include "Software/Compiler/AdvancedCompilation.h"
#include "Exceptions/MemoryException.h"

void initNewTest() {

	Machine::Instance()->clear();
	Model::Instance()->clear();
	Scheduler::Instance()->clear();
	Memory::Instance()->clear();

}

int myAssert(std::ostringstream &s1, Text s2, Text s) {
	if (s1.str() != s2) {
		std::cout << "At (" << s << ") expected output is " << s2
				  << ", but your output is " << s1.str() << std::endl;
		return 0;
	}
	return 1;
}

void test1() {
	int score = 0;
	int maxScore = 0;

	new AddOperation("addop");
	Model::operation("addop")->acceptToken(0, std::make_shared<Token>(3));
	Model::operation("addop")->acceptToken(1, std::make_shared<Token>(2));
	Model::operation("addop")->notify(0);

	std::ostringstream str1;
	str1 << Model::operation("addop")->result->value;
	score += myAssert(str1, "5", "1.1");
	maxScore++;
	//std::cout << Model::operation("addop")->result->value << std::endl;

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

	std::ostringstream str2;
	if (add3->result) str2 << add3->result->value;
	else str2 << "Value not yet calculated";
	score += myAssert(str2, "10", "1.2");
	maxScore++;

//	if (add3->result) std::cout << add3->result->value << std::endl;
//	else std::cout << "Value not yet calculated\n";

	initNewTest();

	Operation *memwr = new MemoryWriteOperation("mw");
	add1 = new AddOperation("a1");
	add2 = new MultOperation("m1");
	add3 = new AddOperation("a2");
	Operation *add4 = new MultOperation("m2");

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

	std::ostringstream str3;
	if (add3->result) str3 << add3->result->value;
	else str3 << "Value not yet calculated";
	score += myAssert(str3, "15", "1.3");
	maxScore++;

	std::ostringstream str4;
	if (add4->result) str4 << add4->result->value;
	else str4 << "Value not yet calculated";
	score += myAssert(str4, "-60", "1.4");
	maxScore++;

	std::cout << "TEST1 finished, result: " << (int) (100.0 * score / maxScore);
	std::cout << "%\n";

	// TODO: add "Value not yet calculated" test

//	if (add3->result) std::cout << add3->result->value << std::endl;
//	else std::cout << "Value not yet calculated\n";
//	if (add4->result) std::cout << add4->result->value << std::endl;
//	else std::cout << "Value not yet calculated\n";
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
	Machine::Instance()->readProgram("../programs/prilogProgramUnchanged.imf");
	Machine::Instance()->execute();
	Machine::Instance()->printLog();
	Memory::Instance()->printMemory();
}

void test4() {
	auto *root = new BinaryOperationExpression("t2", "+");
	auto *rootLeft = new BinaryOperationExpression("t1", "*");
	auto *rToken = new TokenExpression("y");
	auto *llToken = new TokenExpression("2");
	auto *lrToken = new TokenExpression("x");
	root->setOperand(0, rootLeft);
	root->setOperand(1, rToken);
	rootLeft->setOperand(0, llToken);
	rootLeft->setOperand(1, lrToken);
	PrintExpressionVisitor printExpressionVisitor;
	root->accept(&printExpressionVisitor);
	std::cout << "Simple tree example:";
	std::cout << printExpressionVisitor.getOutput() << "\n";
	delete root;

	// Third line in 'prilog' section
	auto *opt1 = new BinaryOperationExpression("t1", "^");
	opt1->setOperand(0, new TokenExpression("x"));
	opt1->setOperand(1, new TokenExpression("3"));

	auto *opt2 = new BinaryOperationExpression("t2", "*");
	opt2->setOperand(0, new TokenExpression("2"));
	opt2->setOperand(1, opt1);

	auto *opt3 = new BinaryOperationExpression("t3", "^");
	opt3->setOperand(0, new TokenExpression("x"));
	opt3->setOperand(1, new TokenExpression("5"));

	auto *opt4 = new BinaryOperationExpression("t4", "^");
	opt4->setOperand(0, new TokenExpression("y"));
	opt4->setOperand(1, new TokenExpression("3"));

	auto *opt5 = new BinaryOperationExpression("t5", "*");
	opt5->setOperand(0, opt3);
	opt5->setOperand(1, opt4);

	auto *opt6 = new BinaryOperationExpression("t6", "+");
	opt6->setOperand(0, opt2);
	opt6->setOperand(1, opt5);

	auto *opt7 = new BinaryOperationExpression("t7", "+");
	opt7->setOperand(0, opt6);
	opt7->setOperand(1, new TokenExpression("5"));

	root = opt7;

	PrintExpressionVisitor printExpressionVisitor2;
	root->accept(&printExpressionVisitor2);
	std::cout << "\nTree example from 'prilog':";
	std::cout << printExpressionVisitor2.getOutput() << std::endl;

	delete root;
}

void test5() {
	initNewTest();
	Program program;
	program.readProgram("../programs/prilogProgram.dbp");
	Compiler compiler(new SimpleCompilation);
	compiler.compile(&program);
	std::cout << std::endl;
	std::cout << program.getName() << ".imf:\n";
	std::cout << compiler.getCompiledCode() << std::endl;
	compiler.saveToImf();
	initNewTest();
	Machine::Instance()->readProgram(program.getImfPath());
	Machine::Instance()->execute();
	Machine::Instance()->printLog();
	Memory::Instance()->printMemory();
	std::cout << Scheduler::Instance()->getCurTime() << std::endl;
}

void test6() {
	initNewTest();
	Program program;
	program.readProgram("../programs/prilogProgram.dbp");
	Compiler compiler(new AdvancedCompilation);
	compiler.compile(&program);
	std::cout << std::endl;
	std::cout << program.getName() << ".imf:\n";
	std::cout << compiler.getCompiledCode() << std::endl;
	compiler.saveToImf();
	initNewTest();
	Machine::Instance()->readProgram(program.getImfPath());
	Machine::Instance()->execute();
	Machine::Instance()->printLog();
	Memory::Instance()->printMemory();
	std::cout << Scheduler::Instance()->getCurTime() << std::endl;
}

void test7() {
	initNewTest();
	try {
		Memory::Instance()->get("noVar");
		std::cout << "NO EXCEPTION??";
	} catch (MemoryException &exception) {
		std::cout << exception.what() << std::endl;
	}
}

void simpleTests() {
	std::cout << "\n------------TEST1------------\n\n";
	test1();
	std::cout << "\n------------TEST2------------\n\n";
	test2();
	std::cout << "\n------------TEST3------------\n\n";
	test3();
	std::cout << "\n------------TEST4------------\n\n";
	test4();
	std::cout << "\n------------TEST5------------\n\n";
	test5();
	std::cout << "\n------------TEST6------------\n\n";
	test6();
	std::cout << "\n------------TEST7------------\n\n";
	test7();
}

bool isCorrect(Text correctPath) {
	std::ifstream correct(correctPath);
	std::stringstream calculated = Memory::Instance()->exportMemory();
	Text corIt, calIt;
	while (correct >> corIt && calculated >> calIt) {
		if (corIt != calIt) return false;
	}
	return true;
}

bool unitTest(size_t idx, Text algorithm) {
	Text testDir = "../programs/unitTests/test";
	if (idx < 10) testDir.append("0");
	testDir.append(std::to_string(idx));
	Text programPath = testDir;
	programPath.append(".dbp");
	testDir.append(".txt");

	initNewTest();

	Program program;
	program.readProgram(programPath);

	ICompilationStrategy *strategy;
	if (algorithm == "simple") {
		strategy = new SimpleCompilation;
	} else if (algorithm == "advanced") {
		strategy = new AdvancedCompilation;
	}
	Compiler compiler(strategy);
	compiler.compile(&program);

	//std::cout << compiler.getCompiledCode() << std::endl;

	compiler.saveToImf();

	Machine::Instance()->readProgram(program.getImfPath());
	Machine::Instance()->execute();
	Machine::Instance()->exportLog(program.getLogPath());

	if (isCorrect(testDir)) {
		std::cout << "Unit Test " << idx << " passed.\n";
		return true;
	} else {
		std::cout << "WRONG ANSWER in unit test " << idx << ".\n";
		return false;
	}

}

int main(int argc, char *argv[]) {

	// TODO: add help
	// TODO: add differing .cfg files to unit tests

	std::stringstream ss;
	for (int i = 0; i < argc; ++i) {
		ss << argv[i] << " ";
	}

	std::map<Text, Text> args;
	Text arg;
	// remove program name
	ss >> arg;

	Text id, val;

	while (std::getline(ss, id, '=')) {
		if (id[0] == ' ') id.erase(0, 1);
		if (id[id.length()-1] == ' ') id.pop_back();
		if (id[0] == '-') {
			id.erase(0, 1);
			args[id] = "true";
		} else {
			std::getline(ss, val, ' ');
			args[id] = val;
		}
	}

	for (auto &&item : args) {
		std::cout << item.first << "=" << item.second << std::endl;
	}

	Text programPath = "../programs/prilogProgram.dbp";;
	Text confPath = "../programs/prilogProgram.cfg";
	bool unitTesting = false;
	bool simpleTesting = false;
	size_t utStart = 1;
	size_t utEnd = 100;
	Text algorithm = "simple";

	if (args.find("pp") != args.end()) programPath = args["pp"];

	if (args.find("cp") != args.end()) confPath = args["cp"];

	if (args.find("ut") != args.end())
		unitTesting = (args["ut"][0] | 32) == 't';

	if (args.find("st") != args.end())
		simpleTesting = (args["st"][0] | 32) == 't';

	if (args.find("utstart") != args.end())
		utStart = std::stoul(args["utstart"]);

	if (args.find("utend") != args.end())
		utEnd = std::stoul(args["utend"]);

	if (args.find("alg") != args.end()) algorithm = args["alg"];

	if (args.find("ut") != args.end()) {

		Model::Instance()->loadConfig(confPath);

		int suc = 0;
		int num = 0;
		for (size_t i = utStart; i < utEnd; i++) {
			suc += unitTest(i, algorithm);
			num++;
		}
		std::cout << "Unit tests done, " << 100.0 * suc / num << "% passed\n";

	} else if (args.find("st") != args.end()) {

		simpleTests();

	} else {

		Model::Instance()->loadConfig(confPath);

		Program program;
		program.readProgram(programPath);

		Compiler compiler(new SimpleCompilation);
		compiler.compile(&program);

		compiler.saveToImf();

		Machine::Instance()->readProgram(program.getImfPath());
		Machine::Instance()->execute();
		Machine::Instance()->exportLog(program.getLogPath());
		Memory::Instance()->printMemory();

	}

	return 0;
}