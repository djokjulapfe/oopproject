#include "AdvancedCompilation.h"
#include "Parser.h"
#include "../Expression/CompositeExpression.h"
#include "../Expression/TokenExpression.h"
#include "../Expression/BinaryOperationExpression.h"
#include "../../Exceptions/NameCollisionException.h"

void AdvancedCompilation::compile(Program *program) {
	auto lines = prepareProgram(program);
	tmpVarCount = 0;
	lineCount = 0;
	compiledCode = "";
	varNames.clear();
	for (auto &&line: lines) {
		auto expr = parseLine(line);
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

CompositeExpression *AdvancedCompilation::parseLine(Text line) {
	opStack.clear();

	auto tokens = Parser::parse(line);

	// Root is '='
	auto rootName = tokens.front();
	tokens.erase(tokens.begin());
	auto rootType = tokens.front();
	tokens.erase(tokens.begin());
	auto *root = new CompositeExpression(1, rootName, rootType);

	root->setOperand(0, subDivide(tokens, "+"));

//	size_t tmpVarCount = 0;
//
//	while (!tokens.empty()) {
//		// TODO: baptize this code
//		if (Parser::isAlphaNum(tokens.back()[0])) {
//			opStack.emplace_back(tokens.back(),
//								 new TokenExpression(tokens.back()));
//		} else if (Parser::isSymbol(tokens.back()[0])) {
//			Text tmpVarName = "t";
//			tmpVarName.append(std::to_string(++tmpVarCount));
//			opStack.emplace_back(tokens.back(),
//								 new BinaryOperationExpression(tmpVarName,
//															   tokens.back()));
//			while (opStack.size() > 2 &&
//				   getPriority(opStack[opStack.size() - 3].first) >=
//				   getPriority(opStack.back().first)) {
//				auto lOperand = opStack[opStack.size() - 2].second;
//				auto rOperand = opStack[opStack.size() - 4].second;
//				if (opStack[opStack.size() - 3].second->isComposite()) {
//					((CompositeExpression *) opStack[opStack.size() - 3].second)
//							->setOperand(0, lOperand);
//					((CompositeExpression *) opStack[opStack.size() - 3].second)
//							->setOperand(1, rOperand);
//				}
//				opStack.erase(opStack.end() - 4);
//				opStack.erase(opStack.end() - 2);
//			}
//		} else {
//			// TODO: throw exception
//		}
//		tokens.pop_back();
//	}
//
//	while (opStack.size() > 1) {
//		auto lOperand = opStack[opStack.size() - 1].second;
//		auto rOperand = opStack[opStack.size() - 3].second;
//		if (opStack[opStack.size() - 2].second->isComposite()) {
//			((CompositeExpression *) opStack[opStack.size() - 2].second)
//					->setOperand(0, lOperand);
//			((CompositeExpression *) opStack[opStack.size() - 2].second)
//					->setOperand(1, rOperand);
//		}
//		opStack.erase(opStack.end() - 3);
//		opStack.erase(opStack.end() - 1);
//	}

//	root->setOperand(0, opStack.front().second);

	return root;
}

Expression *AdvancedCompilation::subDivide(
		std::vector<Text> subLine,
		Text token) {

	// TODO: ensure tmpVarCount is set to 0 before the first call of sD


	Text tmpVarName = "t";
	tmpVarName.append(std::to_string(++tmpVarCount));

	if (token == "^") {

		if (subLine.size() > 1) {

			auto lOperand = new TokenExpression(subLine[0]);

			subLine.erase(subLine.begin() + 0, subLine.begin() + 2);
			auto rOperand = subDivide(subLine, token);

			auto ret = new BinaryOperationExpression(tmpVarName, "^");

			ret->setOperand(0, lOperand);
			ret->setOperand(1, rOperand);
			return ret;

		} else {
			return new TokenExpression(subLine[0]);
		}

	} else {
		// find n/2-th token
		std::vector<size_t> tokenIndecies;
		for (size_t i = 0; i < subLine.size(); ++i) {
			if (token == subLine[i]) {
				tokenIndecies.push_back(i);
			}
		}

		if (!tokenIndecies.empty()) {

			size_t mid_token = tokenIndecies[tokenIndecies.size() / 2];

			// call sD(0, n/2-1) and sD(n/2, n)
			auto lOperand = subDivide(
					std::vector<Text>(subLine.begin(),
									  subLine.begin() + mid_token),
					token);
			auto rOperand = subDivide(
					std::vector<Text>(subLine.begin() + mid_token + 1,
									  subLine.end()),
					token);

			// set the left & right parent
			auto ret = new BinaryOperationExpression(tmpVarName, token);
			ret->setOperand(0, lOperand);
			ret->setOperand(1, rOperand);
			return ret;

		} else {
			// call next token
			return subDivide(subLine, nextToken(token));
		}
	}
	return nullptr;
}

std::vector<Text> AdvancedCompilation::prepareProgram(Program *program) {
	std::map<Text, std::set<Text>> dependency;
	std::map<Text, size_t> numberOfOccurrences;
	std::vector<std::vector<Text>> sortedLines;

	program->seek(0);
	Text cmd;
	while (program->nextCommand(cmd)) {
		auto tokens = Parser::parse(cmd);
		sortedLines.push_back(tokens);
		numberOfOccurrences[tokens[0]] = 0;
		dependency[tokens[0]] = dependentVariables(tokens);
		for (auto &&item : dependency[tokens[0]]) {
			numberOfOccurrences[item]++;
		}
	}

//	size_t debug_iterator = 0;
//	std::sort(sortedLines.begin(), sortedLines.end(),
//			  [&](const std::vector<Text> &lhs, const std::vector<Text> &rhs) -> bool {
//				  // if lhs in dep[rhs]: return false
//				  debug_iterator++;
//				  if (dependency[rhs[0]].find(lhs[0]) == dependency[rhs[0]].end()) return false;
//				  return numberOfOccurrences[lhs[0]] >= numberOfOccurrences[rhs[0]];
//			  });

	for (int i = 0; i < sortedLines.size() - 1; ++i) {
		for (int j = i + 1; j < sortedLines.size(); ++j) {
			auto lhs = sortedLines[i];
			auto rhs = sortedLines[j];
			bool swap;
			if (dependency[lhs[0]].find(rhs[0]) == dependency[lhs[0]].end())
				swap = false;
			else
				swap = numberOfOccurrences[lhs[0]] >=
					   numberOfOccurrences[rhs[0]];
			if (swap) {
				auto tmp = sortedLines[i];
				sortedLines[i] = sortedLines[j];
				sortedLines[j] = tmp;
			}
		}
	}

	std::vector<Text> ret;

	for (auto &&line : sortedLines) {
		Text tit;
		for (auto &&item : line) {
			tit.append(item);
//			std::cout << item << " ";
		}
		ret.push_back(tit);
//		std::cout << std::endl;
	}

	return ret;
}

std::set<Text>
AdvancedCompilation::dependentVariables(std::vector<Text> Tokens) {
	std::set<Text> ret;

	// erase 'varName ='
	Tokens.erase(Tokens.begin(), Tokens.begin() + 1);

	for (auto &&token : Tokens) {
		if (Parser::isLetter(token[0])) {
			ret.insert(token);
		}
	}

	return ret;
}

Text AdvancedCompilation::nextToken(Text token) {
	if (token == "+") {
		return "*";
	} else if (token == "*") {
		return "^";
	}
	return "r u mad m8?";
}
