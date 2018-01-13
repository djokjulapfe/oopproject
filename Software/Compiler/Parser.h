#ifndef OOPPROJECT_PARSER_H
#define OOPPROJECT_PARSER_H


#include "../../Utils/utils.h"

class Parser {

public:
	static std::vector<Text> parse(Text code);

	static bool isLetter(char c);

	static bool isNumber(char c);

	static bool isSymbol(char c);

	static bool isAlphaNum(char c);
};


#endif //OOPPROJECT_PARSER_H
