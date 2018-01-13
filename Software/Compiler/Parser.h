#ifndef OOPPROJECT_PARSER_H
#define OOPPROJECT_PARSER_H


#include "../../Utils/utils.h"

class Parser {

	/**
	 * @brief Helper class for parsing strings.
	 */

public:

	/**
	 * @brief Splits a string to an array of string Tokens.
	 * @param code string to be split
	 * @return split string
	 */
	static std::vector<Text> parse(Text code);

	/**
	 * @brief Checks if the character is a letter of the English alphabet.
	 * @param c character to be checked
	 * @return true if the character is a letter
	 */
	static bool isLetter(char c);

	/**
	 * @brief Checks if the character is a number.
	 * @param c character to be checked
	 * @return true if the character is a number
	 */
	static bool isNumber(char c);

	/**
	 * @brief Checks if the character is a symbol representing an operation.
	 * @param c character to be checked
	 * @return true if the character is a symbol
	 */
	static bool isSymbol(char c);

	/**
	 * @brief Checks if the character is an alphanumeric character (equivalent
	 * to isNumber(c) || isLeter(c)).
	 * @param c character to be checked
	 * @return true if the character is an alphanumeric
	 */
	static bool isAlphaNum(char c);

};


#endif //OOPPROJECT_PARSER_H
