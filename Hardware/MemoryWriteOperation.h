#ifndef OOPPROJECT_MEMORYWRITEOPERATION_H
#define OOPPROJECT_MEMORYWRITEOPERATION_H


#include "MemoryOperation.h"

class MemoryWriteOperation : public MemoryOperation {

public:

	void process() override;

	void accept(Visitor *visitor) override;

	MemoryWriteOperation(Text name = "Memory Write Operation");

};


#endif //OOPPROJECT_MEMORYWRITEOPERATION_H
