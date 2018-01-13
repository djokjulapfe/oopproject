#include "AdvancedCompilation.h"
#include "Parser.h"
#include "../Expression/CompositeExpression.h"
#include "../Expression/TokenExpression.h"
#include "../Expression/BinaryOperationExpression.h"

void AdvancedCompilation::compile(Program *program) {
	auto lines = prepareProgram(program);
	tmpVarCount = 0;
	lineCount = 0;
	compiledCode = "";
	for (auto &&line: lines) {
		auto expr = parseLine(line);
		auto outputExpression1 = expressionToString(expr);
		compiledCode.append(renameTemporaryVariables(outputExpression1));
		delete expr;
	}
	compiledCode.erase(0, 1);
}

CompositeExpression *AdvancedCompilation::parseLine(Text line) {
	//while (!opStack.empty()) opStack.pop();
	// TODO: this might cause a memory leak
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
		// TODO: baptize this code
		// TODO: add isAlphaNum(char c)
		if (Parser::isNumber(tokens.back()[0]) || Parser::isLetter(tokens.back()[0])) {
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
//				  if (dependency[lhs[0]].find(rhs[0]) != dependency[lhs[0]].end()) return false;
//				  return numberOfOccurrences[lhs[0]] >= numberOfOccurrences[rhs[0]];
//			  });

	for (int i = 0; i < sortedLines.size()-1; ++i) {
		for (int j = i + 1; j < sortedLines.size(); ++j) {
			auto lhs = sortedLines[i];
			auto rhs = sortedLines[j];
			bool swap;
			if (dependency[lhs[0]].find(rhs[0]) != dependency[lhs[0]].end()) swap = false;
			else swap = numberOfOccurrences[lhs[0]] >= numberOfOccurrences[rhs[0]];
			if (swap) {
				auto tmp = sortedLines[i];
				sortedLines[i] = sortedLines[j];
				sortedLines[j] = tmp;
			}
		}
	}

	std::vector<Text> ret;

//	for (auto &&line : sortedLines) {
//		Text tit;
//		for (auto &&item : line) {
//			tit.append(item);
//			std::cout << item << " ";
//		}
//		ret.push_back(tit);
//		std::cout << std::endl;
//	}

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
