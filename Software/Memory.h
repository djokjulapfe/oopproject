#ifndef OOPPROJECT_MEMORY_H
#define OOPPROJECT_MEMORY_H


#include "../Utils/utils.h"
#include "../SimulationEngine/Scheduler.h"
#include "../Hardware/Model.h"

class MemoryOperation;

class Memory {
public:

	static Memory *Instance();

	virtual void set(Text varName, double val);

	virtual double get(Text varName);

	virtual void clear();

	virtual void printMemory();

	virtual std::stringstream exportMemory();

	// time until the memory is busy
	virtual Time writeFreeIn();

	virtual void addWriter(MemoryOperation *op);

	// TODO: implement similar functions for reading

	class Thread {

	public:
		std::queue<Operation *> ops;

		// absolute time until the thread is busy;
		Time busyUntil;

		Thread();

		void add(MemoryOperation *op);
	};

protected:

	Memory();

private:

	std::map<Text, double> mem;

	std::vector<Thread> readingThreads, writingThreads;

	Thread *idlestReadingThread();

	Thread *idlestWritingThread();

};


#endif //OOPPROJECT_MEMORY_H
