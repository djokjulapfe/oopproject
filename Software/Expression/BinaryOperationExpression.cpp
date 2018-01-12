#include "BinaryOperationExpression.h"

BinaryOperationExpression::BinaryOperationExpression(Text name, Text operationType)
		: CompositeExpression(2, name, operationType) {
	this->name = name;
}
