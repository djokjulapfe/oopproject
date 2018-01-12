#include "Expression.h"

const Text &Expression::getName() const {
	return name;
}

Expression::~Expression() {

}

Expression::Expression(const Text &name) : name(name) {
}
