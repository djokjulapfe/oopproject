#ifndef OOPPROJECT_MEMORYWRITEOPERATION_H
#define OOPPROJECT_MEMORYWRITEOPERATION_H


#include "MemoryOperation.h"

class MemoryWriteOperation : public MemoryOperation {

	/**
	 * @brief Writes a value to memory.
	 *
	 * result.value = inputPort[0].value
	 * memory[name] = inputPort[0].value
	 */

public:

	void process() override;

	void accept(Visitor *visitor) override;

	explicit MemoryWriteOperation(Text name = "Memory Write Operation");

	void acceptToken(size_t idx, std::shared_ptr<Token> token) override;

};


#endif //OOPPROJECT_MEMORYWRITEOPERATION_H
