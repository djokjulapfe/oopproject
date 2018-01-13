#include "AdvancedCompilation.h"
#include "Parser.h"
#include "../Expression/CompositeExpression.h"
#include "../Expression/TokenExpression.h"
#include "../Expression/BinaryOperationExpression.h"
#include "../../Exceptions/NameCollisionException.h"

void AdvancedCompilation::compile(Program *program) {

	// rearrange the lines to minimize waiting on memory writing operations
	auto lines = prepareProgram(program);

	// initialize variables
	tmpVarCount = 0;
	lineCount = 0;
	compiledCode = "";
	varNames.clear();

	// loop through the commands
	for (auto &&line: lines) {

		// parse a single line
		auto expr = parseLine(line);

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

CompositeExpression *AdvancedCompilation::parseLine(Text line) {

	// parse the line to an list of tokens
	auto tokens = Parser::parse(line);

	// create the root token
	auto rootName = tokens.front();
	tokens.erase(tokens.begin());
	auto rootType = tokens.front();
	tokens.erase(tokens.begin());
	auto *root = new CompositeExpression(1, rootName, rootType);

	// set it's only operand to the expression given by subDivide
	root->setOperand(0, subDivide(tokens, "+"));

	return root;

}

Expression *AdvancedCompilation::subDivide(
		std::vector<Text> subLine,
		Text token) {

	// name of the expression
	Text tmpVarName = "t";
	tmpVarName.append(std::to_string(++tmpVarCount));

	if (token == "^") {

		// if the token is a '^' add it as a right associative operation
		if (subLine.size() > 1) {

			// create the left token
			auto lOperand = new TokenExpression(subLine[0]);

			// remove the operand and the operation name
			subLine.erase(subLine.begin() + 0, subLine.begin() + 2);

			// continue recursion
			auto rOperand = subDivide(subLine, token);

			// create new binary operation expression
			auto ret = new BinaryOperationExpression(tmpVarName, "^");

			// set it's operands
			ret->setOperand(0, lOperand);
			ret->setOperand(1, rOperand);

			return ret;

		} else {

			// if there is only one token than it is a variable or a constant
			// and stop the recursion
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

		// if there are tokens continue with the recursion
		if (!tokenIndecies.empty()) {

			// the index of the token in the middle
			size_t mid_token = tokenIndecies[tokenIndecies.size() / 2];

			// calls subDivide for the left subarray
			auto lOperand = subDivide(
					std::vector<Text>(subLine.begin(),
									  subLine.begin() + mid_token),
					token);

			// calls subDivide for the right subarray
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

			// if there are no tokens left continue recursion with the next
			// token
			return subDivide(subLine, nextToken(token));

		}
	}
}

std::vector<Text> AdvancedCompilation::prepareProgram(Program *program) {

	std::map<Text, std::set<Text>> dependency;
	std::map<Text, size_t> numberOfOccurrences;
	std::vector<std::vector<Text>> sortedLines;

	// create the dependency table
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

	// sort the lines in the descending numberOfOccurances order with no
	// variable having dependecies before it's assignment
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

	// append all lines to the output
	for (auto &&line : sortedLines) {
		Text tit;
		for (auto &&item : line) {
			tit.append(item);
		}
		ret.push_back(tit);
	}

	return ret;

}

std::set<Text>
AdvancedCompilation::dependentVariables(std::vector<Text> Tokens) {

	std::set<Text> ret;

	// erase 'varName ='
	Tokens.erase(Tokens.begin(), Tokens.begin() + 1);

	// loop and find the dependant variables
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
	} else return "r u mad m8?";

}
