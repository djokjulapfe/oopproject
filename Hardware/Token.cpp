#include "Token.h"

double Token::getValue() const {
	return value;
}

void Token::setValue(double value) {
	Token::value = value;
}

Token::Token() {
	value = 0;
	name = "Unnamed Token";
	producedBy = nullptr;
}

Token::Token(double value, Text name) : value(value), name(name) {
	producedBy = nullptr;
}
