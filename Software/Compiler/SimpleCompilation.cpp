#include <iostream>
#include <sstream>
#include "SimpleCompilation.h"
#include "../Expression/CompositeExpression.h"
#include "../Expression/TokenExpression.h"
#include "../Expression/BinaryOperationExpression.h"
#include "Parser.h"
#include "../../Exceptions/BadExpressionException.h"
#include "../../Exceptions/NameCollisionException.h"

void SimpleCompilation::compile(Program *program) {
	Text programLine;
	tmpVarCount = 0;
	lineCount = 0;
	compiledCode = "";
	varNames.clear();
	while (program->nextCommand(programLine)) {
		auto expr = parseLine(programLine);
		auto outputExpression1 = expressionToString(expr);
		compiledCode.append(renameTemporaryVariables(outputExpression1));
		if (varNames.find(expr->getName()) == varNames.end()) {
			varNames.insert(expr->getName());
		} else {
			Text msg = "There already exists a variable with the name ";
			msg.append(expr->getName());
			delete expr;
			throw NameCollisionException(msg);
		}
		delete expr;
	}
	compiledCode.erase(0, 1);
}

CompositeExpression *SimpleCompilation::parseLine(Text line) {

	opStack.clear();

	auto tokens = Parser::parse(line);

	// Root is '='
	auto rootName = tokens.front();
	tokens.erase(tokens.begin());
	auto rootType = tokens.front();
	tokens.erase(tokens.begin());
	auto *root = new CompositeExpression(1, rootName, rootType);

	size_t tmpVarCount = 0;

	while (!tokens.empty()) {
		if (Parser::isAlphaNum(tokens.back()[0])) {
			opStack.emplace_back(tokens.back(),
								 new TokenExpression(tokens.back()));
		} else if (Parser::isSymbol(tokens.back()[0])) {
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
				if (opStack[opStack.size() - 3].second->isComposite()) {
					((CompositeExpression *) opStack[opStack.size() - 3].second)
							->setOperand(0, lOperand);
					((CompositeExpression *) opStack[opStack.size() - 3].second)
							->setOperand(1, rOperand);
				} else {
					// TODO: throw exception
				}
				opStack.erase(opStack.end() - 4);
				opStack.erase(opStack.end() - 2);
			}
		} else {
			Text msg = "No token with the name ";
			msg.append(tokens.back());
			msg.append(" when translating:\n");
			msg.append(line);
			throw BadExpressionException(msg);
		}
		tokens.pop_back();
	}

	while (opStack.size() > 1) {
		auto lOperand = opStack[opStack.size() - 1].second;
		auto rOperand = opStack[opStack.size() - 3].second;
		if (opStack[opStack.size() - 2].second->isComposite()) {
			((CompositeExpression *) opStack[opStack.size() - 2].second)
					->setOperand(0, lOperand);
			((CompositeExpression *) opStack[opStack.size() - 2].second)
					->setOperand(1, rOperand);
		} else {
			// TODO: throw exception
		}
		opStack.erase(opStack.end() - 3);
		opStack.erase(opStack.end() - 1);
	}

	root->setOperand(0, opStack.front().second);

	return root;
}