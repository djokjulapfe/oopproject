#ifndef OOPPROJECT_MACHINE_H
#define OOPPROJECT_MACHINE_H


#include <set>
#include <map>
#include "../Hardware/Operation.h"

class Machine {

public:

	static Machine* Instance();

	virtual void toExecute(ITimedOperation *operation);

	virtual void toCompleted(ITimedOperation *operation);

	virtual void addOp(ITimedOperation *operation);

	// Loads an imf file and creates the waiting pool
	virtual void readProgram(Text imfPath);

	// Calls Operation::send() in executing -> completed transition
	virtual void execute();

	virtual void printLog();

	virtual void exportLog(Text programPath);

	virtual void clear();

protected:

	Machine();

private:

	Text programName;

	std::set<ITimedOperation *> waiting, executing, completed;
	std::map<ITimedOperation *, Text> operationToLabel;

	class LogElement {

	public:

		LogElement(const Text &label, Time start, Time end);

		class Compare {

		public:

			static bool cmp(const LogElement &lhs, const LogElement &rhs);

			bool operator()(const LogElement &lhs, const LogElement &rhs) {
				return cmp(lhs, rhs);
			}
		};

		Text label;
		Time start, end;

	};

	std::set<LogElement, LogElement::Compare> logs;

	// Helper Functions

	void addArgument(size_t idx, Text opTo, Text opFrom);

};


#endif //OOPPROJECT_MACHINE_H
