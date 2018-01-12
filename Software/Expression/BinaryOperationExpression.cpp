#include "BinaryOperationExpression.h"

BinaryOperationExpression::BinaryOperationExpression(Text name, Text operationType)
		: CompositeExpression(2, operationType) {
	this->name = name;
}
