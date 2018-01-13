#ifndef OOPPROJECT_MEMORY_H
#define OOPPROJECT_MEMORY_H


#include "../Utils/utils.h"
#include "../SimulationEngine/Scheduler.h"
#include "../Hardware/Model.h"

class MemoryOperation;

class Memory {

	/**
	 * @brief Manages variables and their values
	 */

public:

	/**
	 * @brief Singleton design pattern.
	 * @return pointer to the instance
	 */
	static Memory *Instance();

	/**
	 * @brief Writes to a memory location.
	 * @param varName name of the variable to be written
	 * @param val value of the variable to be written
	 */
	virtual void set(Text varName, double val);

	/**
	 * @brief Reads from a memory location.
	 * @param varName name of the variable to be read
	 * @return value of the read variable
	 * @throws VarNotAvailableException
	 */
	virtual double get(Text varName);

	/**
	 * @brief Clears all variables from the memory.
	 */
	virtual void clear();

	/**
	 * @brief Prints current content of the memory to the standard output.
	 */
	virtual void printMemory();

	/**
	 * @brief Exports current content of the memory to a stringstream
	 * @return stringstream of the memory
	 */
	virtual std::stringstream exportMemory();

	/**
	 * @brief Calculates the busyness of the write threads
	 * @return timestamp when the memory will be ready for writing
	 */
	virtual Time writeFreeIn();

	/**
	 * @brief Updates writing thread busyness.
	 * @param op operation that should be called when memory is ready
	 */
	virtual void addWriter(MemoryOperation *op);

	/**
	 * @brief Calculates the busyness of the read threads
	 * @return timestamp when the memory will be ready for reading
	 */
	virtual Time readFreeIn();

	/**
	 * @brief Updates reading thread busyness.
	 * @param op operation that should be called when memory is ready
	 */
	virtual void addReader(MemoryOperation *op);

	class Thread {

		/**
		 * @brief Helper class to manage multiple simultaneous processes
		 */

	public:

		// Operations that are waitng for a call
		std::queue<Operation *> ops;

		// Absolute time until the thread is busy;
		Time busyUntil;

		/**
		 * @brief Default constructor.
		 */
		Thread();

		/**
		 * @brief Updates the queue and the busyness
		 * @param op Operation that is taking resources
		 */
		void add(MemoryOperation *op);
	};

protected:

	/**
	 * @brief Default constructor.
	 */
	Memory();

private:

	// Maps variable names to their values
	std::map<Text, double> mem;

	// List of reading and writing threads
	std::vector<Thread> readingThreads, writingThreads;

	/**
	 * @brief Calculates which reading thread will be free earliest
	 * @return The thread that can accept an operation the fastes
	 */
	Thread *idlestReadingThread();

	/**
	 * @brief Calculates which writing thread will be free earliest
	 * @return The thread that can accept an operation the fastes
	 */
	Thread *idlestWritingThread();

};


#endif //OOPPROJECT_MEMORY_H
