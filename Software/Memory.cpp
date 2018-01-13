#include <climits>
#include <iostream>
#include <sstream>
#include "Memory.h"
#include "../Hardware/MemoryOperation.h"
#include "../Exceptions/VarNotAvailableException.h"

Memory *Memory::Instance() {
	static Memory instance;
	return &instance;
}

void Memory::set(Text varName, double val) {
	mem[varName] = val;
}

double Memory::get(Text varName) {
	if (mem.find(varName) == mem.end()) {
		Text msg = "Trying to access ";
		msg.append(varName);
		clear();
		throw VarNotAvailableException(msg);
	}
	return mem[varName];
}

Memory::Memory() : readingThreads(Model::Instance()->Nr),
				   writingThreads(Model::Instance()->Nw) {
}

void Memory::addWriter(MemoryOperation *op) {
	Thread *idlest = idlestWritingThread();
	idlest->add(op);
}

void Memory::addReader(MemoryOperation *op) {
	Thread *idlest = idlestReadingThread();
	idlest->add(op);
}

Time Memory::writeFreeIn() {
	Thread *idlest = idlestWritingThread();
	if (idlest->busyUntil > Scheduler::Instance()->getCurTime()) {
		return idlest->busyUntil - Scheduler::Instance()->getCurTime();
	}
	return 0;
}

Time Memory::readFreeIn() {
	Thread *idlest = idlestReadingThread();
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
		std::cout << item.first << " = " << (size_t) item.second << std::endl;
	}
}

std::stringstream Memory::exportMemory() {
	std::stringstream ret;
	for (auto &&item : mem) {
		ret << item.first << " = " << (size_t)item.second << std::endl;
	}
	return ret;
}

void Memory::Thread::add(MemoryOperation *op) {
	op->owningThread = this;
	if (busyUntil > Scheduler::Instance()->getCurTime()) {
		ops.push(op);
	}

	// Calculate time
	Time curTime = Scheduler::Instance()->getCurTime();
	if (curTime > busyUntil) {
		busyUntil = curTime + op->opTime;
	} else {
		busyUntil += op->opTime;
	}
}

Memory::Thread::Thread() : busyUntil(0) {
}
