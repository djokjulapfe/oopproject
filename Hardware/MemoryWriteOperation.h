#ifndef OOPPROJECT_MEMORYWRITEOPERATION_H
#define OOPPROJECT_MEMORYWRITEOPERATION_H


#include "MemoryOperation.h"

class MemoryWriteOperation : public MemoryOperation {

public:

	void process() override;

	void accept(Visitor *visitor) override;

	explicit MemoryWriteOperation(Text name = "Memory Write Operation");

	void acceptToken(size_t idx, std::shared_ptr<Token> token) override;

};


#endif //OOPPROJECT_MEMORYWRITEOPERATION_H
