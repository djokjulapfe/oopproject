#include "Parser.h"
#include "../../Exceptions/BadExpressionException.h"


bool Parser::isLetter(char c) {
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool Parser::isNumber(char c) {
	return c >= '0' && c <= '9';
}

bool Parser::isSymbol(char c) {
	return c == '=' || c == '+' || c == '*' || c == '^';
}

bool Parser::isAlphaNum(char c) {
	return isLetter(c) || isNumber(c);
}

std::vector<Text> Parser::parse(Text text) {

	std::vector<Text> ret;

	// remove blank spaces
	text.erase(std::remove_if(text.begin(), text.end(),
							  [=](char c) {
								  return c == ' ';
							  }), text.end());

	// go through the text
	while (text.length() > 0) {

		Text token;

		// extract a token
		if (isLetter(text[0])) {
			while (text.length() > 0 && isAlphaNum(text[0])) {
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
			Text msg = "Can't parse this line:\n";
			msg.append(text);
			throw BadExpressionException(msg);
		}

		// add the token to the return value
		ret.push_back(token);

	}

	return ret;
}
