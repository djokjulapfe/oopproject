#ifndef OOPPROJECT_MEMORYREADOPERATION_H
#define OOPPROJECT_MEMORYREADOPERATION_H


#include "MemoryOperation.h"

class MemoryReadOperation : public MemoryOperation {

public:

	void process() override;

	void accept(Visitor *visitor) override;

	explicit MemoryReadOperation(Text name = "Memory Write Operation");

	void acceptToken(size_t idx, std::shared_ptr<Token> token) override;
};


#endif //OOPPROJECT_MEMORYREADOPERATION_H
