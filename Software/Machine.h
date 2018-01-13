#ifndef OOPPROJECT_MACHINE_H
#define OOPPROJECT_MACHINE_H


#include <set>
#include <map>
#include "../Hardware/Operation.h"

class Machine {

	/**
	 * @brief Manages the flow of tokens and creation of the log files.
	 */

public:

	/**
	 * @brief Singleton design pattern.
	 * @return pointer to the instance
	 */
	static Machine* Instance();

	/**
	 * @brief Upgrades an operation from waiting to executing.
	 * @param operation operation that should be upgraded
	 */
	virtual void toExecute(ITimedOperation *operation);

	/**
	 * @brief Upgrades an operation from executing to completed.
	 * @param operation operation that should be upgraded
	 */
	virtual void toCompleted(ITimedOperation *operation);

	/**
	 * @brief Adds a new operation te waiting.
	 * @param operation operation to be added
	 */
	virtual void addOp(ITimedOperation *operation);

	/**
	 * @brief Loads an imf file and creates the waiting pool.
	 * @param imfPath path to the imf file
	 */
	virtual void readProgram(Text imfPath);

	/**
	 * @brief Runs the Scheduler.
	 */
	virtual void execute();

	/**
	 * @brief Prints the log to the standard output.
	 */
	virtual void printLog();

	/**
	 * @brief Prints the log to a .log file.
	 * @param logPath path to the .log file
	 */
	virtual void exportLog(Text logPath);

	/**
	 * @brief Empties all internal containers
	 */
	virtual void clear();

protected:

	/**
	 * @brief Default constructor.
	 */
	Machine();

private:

	// Name of the program that is run
	Text programName;

	// Pools for different operations
	std::set<ITimedOperation *> waiting, executing, completed;

	// Maps operations to their labels
	std::map<ITimedOperation *, Text> operationToLabel;

	class LogElement {

		/**
		 * @brief Helper class for creating the log file.
		 */

	public:

		/**
		 * @brief Default constructor.
		 * @param label of the operation that is run
		 * @param start time of the operation
		 * @param end time of the operation
		 */
		LogElement(const Text &label, Time start, Time end);

		class Compare {

			/**
			 * @brief Compare class for the std::set's compare parameter
			 */

		public:

			/**
			 * @brief Compares two LogElements.
			 * @param lhs Left Hand Side
			 * @param rhs Right Hand Side
			 * @return comparisson check
			 */
			static bool cmp(const LogElement &lhs, const LogElement &rhs);

			/**
			 * @brief Operator used by the std::set.
			 * @param lhs Left Hand Side
			 * @param rhs Right Hand Side
			 * @return comparisson check
			 */
			bool operator()(const LogElement &lhs, const LogElement &rhs) {
				return cmp(lhs, rhs);
			}
		};

		// Label of the operation
		Text label;

		// Start and end times
		Time start, end;

	};

	// set of log elements stored in correct order
	std::set<LogElement, LogElement::Compare> logs;

	/**
	 * @brief Helper function for adding an argument to a operation.
	 * @param idx index of the operand that opTo should get
	 * @param opTo operator being assigned an argument
	 * @param opFrom expression that is being assigned to opTo
	 */
	void addArgument(size_t idx, Text opTo, Text opFrom);

};


#endif //OOPPROJECT_MACHINE_H
