#include <iostream>
#include <sstream>
#include "SimpleCompilation.h"
#include "../Expression/CompositeExpression.h"
#include "../Expression/TokenExpression.h"
#include "../Expression/BinaryOperationExpression.h"

void SimpleCompilation::compile(Program *program) {
	Text programLine;
	tmpVarCount = 0;
	lineCount = 0;
	compiledCode = "";
	while (program->nextCommand(programLine)) {
		auto expr = parseLine(programLine);
		auto outputExpression1 = outputExpression(expr);
		compiledCode.append(renameTemporaryVariables(outputExpression1));
		//std::cout << renameTemporaryVariables(outputExpression1) << std::endl;
		delete expr;
	}
	compiledCode.erase(0, 1);
}

Text SimpleCompilation::renameTemporaryVariables(Text code) {
	// TODO: remove dependecy on not having variables with name 't#*'
	if (code.empty()) {
		// TODO: throw exception?
		std::cout << "Empty string passed to renameTemporaryVariable\n";
		return "";
	}
	std::map<Text, Text> oldToNew;
	std::vector<Text> lines;
	std::stringstream ss(code);
	Text to;
	while (ss >> to) {
		if (to.length() > 1 && to[0] == 't' && isNumber(to[1])) {
			if (oldToNew.find(to) == oldToNew.end()) {
				Text tmpName = "t";
				tmpName.append(std::to_string(++tmpVarCount));
				oldToNew[to] = tmpName;
			}
		}
	}

	std::stringstream ss2(code);
	std::stringstream newss;

	while (ss2 >> to) {
		if (oldToNew.find(to) != oldToNew.end()) {
			newss << oldToNew[to] << " ";
		} else if (isSymbol(to[0])){
			newss << std::endl << ++lineCount << ": " << to << " ";
		} else {
			newss << to << " ";
		}
	}

	return newss.str();
}

CompositeExpression *SimpleCompilation::parseLine(Text line) {
	//while (!opStack.empty()) opStack.pop();
	// TODO: this might cause a memory leak
	opStack.clear();


	auto tokens = split(line, ' ');

	// Root is '='
	auto rootName = tokens.front();
	tokens.pop_front();
	auto rootType = tokens.front();
	tokens.pop_front();
	auto *root = new CompositeExpression(1, rootName, rootType);

	size_t tmpVarCount = 0;

	while (!tokens.empty()) {
		// TODO: baptize this code
		// TODO: add isAlphaNum(char c)
		if (isNumber(tokens.back()[0]) || isLetter(tokens.back()[0])) {
			opStack.emplace_back(tokens.back(),
								 new TokenExpression(tokens.back()));
		} else if (isSymbol(tokens.back()[0])) {
			Text tmpVarName = "t";
			tmpVarName.append(std::to_string(++tmpVarCount));
			opStack.emplace_back(tokens.back(),
								 new BinaryOperationExpression(tmpVarName,
															   tokens.back()));
			while (opStack.size() > 2 &&
				   getPriority(opStack[opStack.size() - 3].first) >=
				   getPriority(opStack.back().first)) {
				auto lOperand = opStack[opStack.size() - 2].second;
				auto rOperand = opStack[opStack.size() - 4].second;
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
		tokens.pop_back();
	}

	// TODO: fix when ending with a '^'
	while (opStack.size() > 1) {
		auto lOperand = opStack[opStack.size() - 1].second;
		auto rOperand = opStack[opStack.size() - 3].second;
		// TODO: add isComposite()
		((CompositeExpression *) opStack[opStack.size() - 2].second)
				->setOperand(0, lOperand);
		((CompositeExpression *) opStack[opStack.size() - 2].second)
				->setOperand(1, rOperand);
		opStack.erase(opStack.end() - 3);
		opStack.erase(opStack.end() - 1);
	}

	root->setOperand(0, opStack.front().second);

	return root;
}

std::deque<Text> SimpleCompilation::split(Text text, char delimiter) {
	std::deque<Text> ret;
	text.erase(std::remove_if(text.begin(), text.end(),
							  [=](char c) {
								  return c == delimiter;
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
			std::cout << "Bad expression!\n";
			text.erase(0, 1);
		}
		ret.push_back(token);
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
