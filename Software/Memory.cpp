#include <climits>
#include <iostream>
#include "Memory.h"
#include "../Hardware/MemoryOperation.h"

Memory *Memory::Instance() {
	static Memory instance;
	return &instance;
}

void Memory::set(Text varName, double val) {
	mem[varName] = val;
}

double Memory::get(Text varName) {
	return mem[varName];
}

Memory::Memory() : readingThreads(Model::Instance()->Nr),
				   writingThreads(Model::Instance()->Nw) {
}

void Memory::addWriter(MemoryOperation *op) {
	Thread *idlest = idlestWritingThread();
	idlest->add(op);
}

Time Memory::writeFreeIn() {
	Thread *idlest = idlestWritingThread();
	if (idlest->busyUntil > Scheduler::Instance()->getCurTime()) {
		return idlest->busyUntil - Scheduler::Instance()->getCurTime();
	}
	return 0;
}

Memory::Thread *Memory::idlestReadingThread() {
	Thread *ret = nullptr;
	Time min = ULONG_MAX;
	for (auto &&readingThread : readingThreads) {
		if (readingThread.busyUntil < min) {
			min = readingThread.busyUntil;
			ret = &readingThread;
		}
	}
	return ret;
}

Memory::Thread *Memory::idlestWritingThread() {
	Thread *ret = nullptr;
	Time min = ULONG_MAX;
	for (auto &&writingThread : writingThreads) {
		if (writingThread.busyUntil < min) {
			min = writingThread.busyUntil;
			ret = &writingThread;
		}
	}
	return ret;
}

void Memory::clear() {
	for (auto &&writingThread : writingThreads) {
		writingThread.busyUntil = 0;
		while (!writingThread.ops.empty()) writingThread.ops.pop();
	}
	for (auto &&readingThread : readingThreads) {
		readingThread.busyUntil = 0;
		while (!readingThread.ops.empty()) readingThread.ops.pop();
	}
	mem.clear();
}

void Memory::printMemory() {
	for (auto &&item : mem) {
		std::cout << item.first << " = " << item.second << std::endl;
	}
}

void Memory::Thread::add(MemoryOperation *op) {
	op->owningThread = this;
	if (busyUntil > Scheduler::Instance()->getCurTime()) {
		ops.push(op);
	}

	// Calculate time
	Time curTime = Scheduler::Instance()->getCurTime();
	if (curTime > busyUntil) {
		// TODO: add a flag for r/w
		busyUntil = curTime + Model::Instance()->Mw;
	} else {
		busyUntil += Model::Instance()->Mw;
	}
}

Memory::Thread::Thread() : busyUntil(0) {
}
