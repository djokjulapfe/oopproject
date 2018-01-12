#ifndef OOPPROJECT_BINARYOPERATION_H
#define OOPPROJECT_BINARYOPERATION_H


#include "CompositeExpression.h"

class BinaryOperationExpression : public CompositeExpression {

public:

	explicit BinaryOperationExpression(Text name, Text operationType);

};


#endif //OOPPROJECT_BINARYOPERATION_H
