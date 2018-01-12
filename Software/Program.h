#ifndef OOPPROJECT_PROGRAM_H
#define OOPPROJECT_PROGRAM_H


#include "../Utils/utils.h"

class Program {

public:

	static Program* Instance();

	virtual void readProgram(Text programPath);

	virtual bool nextCommand(Text &command);

	const Text &getName() const;

protected:

	Program() = default;

private:

	std::queue<Text> lines;

	Text name;

};


#endif //OOPPROJECT_PROGRAM_H
