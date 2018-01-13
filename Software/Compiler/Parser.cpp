#include "Parser.h"



bool Parser::isLetter(char c) {
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool Parser::isNumber(char c) {
	return c >= '0' && c <= '9';
}

bool Parser::isSymbol(char c) {
	return c == '=' || c == '+' || c == '*' || c == '^';
}

std::vector<Text> Parser::parse(Text text) {
	std::vector<Text> ret;
	text.erase(std::remove_if(text.begin(), text.end(),
							  [=](char c) {
								  return c == ' ';
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

	return ret;
}
