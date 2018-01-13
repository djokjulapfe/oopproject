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

	// initialize variables
	Text programLine;
	tmpVarCount = 0;
	lineCount = 0;
	compiledCode = "";
	varNames.clear();

	// get each command
	while (program->nextCommand(programLine)) {

		// parse a single line
		auto expr = parseLine(programLine);

		// convert it to a string
		auto outputExpression1 = expressionToString(expr);

		// rename temporary variables
		compiledCode.append(renameTemporaryVariables(outputExpression1));

		// add the name of the variable at the beginning of the line to varNames
		if (varNames.find(expr->getName()) == varNames.end()) {
			varNames.insert(expr->getName());
		} else {
			Text msg = "There already exists a variable with the name ";
			msg.append(expr->getName());
			delete expr;
			throw NameCollisionException(msg);
		}

		// delete the expression
		delete expr;

	}

	// remove leading newline
	compiledCode.erase(0, 1);

}

CompositeExpression *SimpleCompilation::parseLine(Text line) {

	opStack.clear();

	// parse a line
	auto tokens = Parser::parse(line);

	// create the root expression
	auto rootName = tokens.front();
	tokens.erase(tokens.begin());
	auto rootType = tokens.front();
	tokens.erase(tokens.begin());
	auto *root = new CompositeExpression(1, rootName, rootType);

	size_t tmpVarCount = 0;

	// loop thorough all the tokens
	while (!tokens.empty()) {

		if (Parser::isAlphaNum(tokens.back()[0])) {

			// add it as a variable/constant
			opStack.emplace_back(tokens.back(),
								 new TokenExpression(tokens.back()));

		} else if (Parser::isSymbol(tokens.back()[0])) {

			// create a temporary name
			Text tmpVarName = "t";
			tmpVarName.append(std::to_string(++tmpVarCount));

			// create a binary operation with this name
			opStack.emplace_back(tokens.back(),
								 new BinaryOperationExpression(tmpVarName,
															   tokens.back()));

			// pop operations with lower priority
			while (opStack.size() > 2 &&
				   getPriority(opStack[opStack.size() - 3].first) >=
				   getPriority(opStack.back().first)) {

				// get the left and right operands
				auto lOperand = opStack[opStack.size() - 2].second;
				auto rOperand = opStack[opStack.size() - 4].second;

				// odd the operands to the middle operation
				if (opStack[opStack.size() - 3].second->isComposite()) {
					((CompositeExpression *) opStack[opStack.size() - 3].second)
							->setOperand(0, lOperand);
					((CompositeExpression *) opStack[opStack.size() - 3].second)
							->setOperand(1, rOperand);
				} else {
					// TODO: throw exception
				}

				// remove the operands from the stack
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

	// when the tokens were read, pop any remaining operations
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

	// set the root operand to the operation that is left in the stack
	root->setOperand(0, opStack.front().second);

	return root;

}