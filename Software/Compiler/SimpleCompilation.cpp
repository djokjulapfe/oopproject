#include <iostream>
#include "SimpleCompilation.h"
#include "../Expression/CompositeExpression.h"
#include "../Expression/TokenExpression.h"
#include "../Expression/BinaryOperationExpression.h"

void SimpleCompilation::compile(Program *program) {
	Text programLine;
	while (program->nextCommand(programLine)) {
		auto expr = parseLine(programLine);
		outputExpression(expr);
		delete expr;
	}
}

CompositeExpression *SimpleCompilation::parseLine(Text line) {
	//while (!opStack.empty()) opStack.pop();
	// TODO: this might cause a memory leak
	opStack.clear();


	auto tokens = split(line);

	// Root is =
	auto rootName = tokens.front();
	tokens.pop();
	auto rootType = tokens.front();
	tokens.pop();
	auto *root = new CompositeExpression(1, rootName, rootType);

	size_t tmpVarCount = 0;

//	if isAlphaNum(..):
//		opStack.push(<tokens.front, new TokenExpr(tokens.front>) # adds new token
//	if isSymbol(..):
//		opStack.push(<tokens.front, new BinOpExpr("tx", tokens.front)>) # adds new op
//		if (opStack[opStack.size - 2].priority => opStack.back.priority):
//			opStack[o.s - 2].setOperand(0, opStack[o.s - 3])
//			opStack[o.s - 2].setOperand(1, opStack[o.s - 1])
//			opStack.remove(-3).remove(-1)
//

	while (!tokens.empty()) {
		// TODO: baptize this code
		// TODO: add isAlphaNum(char c)
		std::cout << "Processing: " << tokens.front() << std::endl;
		if (isNumber(tokens.front()[0]) || isLetter(tokens.front()[0])) {
			opStack.emplace_back(tokens.front(),
								 new TokenExpression(tokens.front()));
		} else if (isSymbol(tokens.front()[0])) {
			Text tmpVarName = "t";
			tmpVarName.append(std::to_string(++tmpVarCount));
			opStack.emplace_back(tokens.front(),
								 new BinaryOperationExpression(tmpVarName,
															   tokens.front()));
			while (opStack.size() > 2 &&
				   getPriority(opStack[opStack.size() - 3].first) >=
				   getPriority(opStack.back().first)) {
				auto lOperand = opStack[opStack.size() - 4].second;
				auto rOperand = opStack[opStack.size() - 2].second;
				// TODO: add isComposite()
				((CompositeExpression *) opStack[opStack.size() - 3].second)
						->setOperand(0, lOperand);
				((CompositeExpression *) opStack[opStack.size() - 3].second)
						->setOperand(1, rOperand);
				opStack.erase(opStack.end() - 4);
				opStack.erase(opStack.end() - 2);
			}
		} else {
			// TODO: throw exception
		}
		tokens.pop();
	}

	if (opStack.size() == 3) {
		auto lOperand = opStack[0].second;
		auto rOperand = opStack[2].second;
		// TODO: add isComposite()
		((CompositeExpression *) opStack[1].second)
				->setOperand(0, lOperand);
		((CompositeExpression *) opStack[1].second)
				->setOperand(1, rOperand);
		opStack.erase(opStack.begin() + 0);
		opStack.erase(opStack.begin() + 1);
	}

	root->setOperand(0, opStack.front().second);

	return root;
}

std::queue<Text> SimpleCompilation::split(Text text) {
	std::queue<Text> ret;
	text.erase(std::remove_if(text.begin(), text.end(),
							  [](char c) {
								  return c == ' ' || c == '\n';
							  }), text.end());

	while (text.length() > 0) {
		Text token;
		if (isLetter(text[0])) {
			while (text.length() > 0 &&
				   (isLetter(text[0]) || isNumber(text[0]))) {
				token.append(1, text[0]);
				text.erase(0, 1);
			}
		} else if (isNumber(text[0])) {
			while (text.length() > 0 && isNumber(text[0])) {
				token.append(1, text[0]);
				text.erase(0, 1);
			}
		} else if (isSymbol(text[0])) {
			while (text.length() > 0 && isSymbol(text[0])) {
				token.append(1, text[0]);
				text.erase(0, 1);
			}
		} else {
			// TODO: add exceptions here
			std::cout << "Bad expression!";
		}
		ret.push(token);
	}

	// This works when using std::vector<Text>, and not with std::queue
//	std::cout << "Tokens: [";
//	for (int i = 0; i < ret.size() - 1; ++i) {
//		std::cout << ret[i] << ", ";
//	}
//	std::cout << ret[ret.size() - 1] << "]\n";

	return ret;
}

bool SimpleCompilation::isLetter(char c) {
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool SimpleCompilation::isNumber(char c) {
	return c >= '0' && c <= '9';
}

bool SimpleCompilation::isSymbol(char c) {
	return c == '=' || c == '+' || c == '*' || c == '^';
}
