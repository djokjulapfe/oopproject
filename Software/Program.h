#ifndef OOPPROJECT_PROGRAM_H
#define OOPPROJECT_PROGRAM_H


#include "../Utils/utils.h"

class Program {

public:

	Program() = default;

	virtual void readProgram(Text programPath);

	virtual bool nextCommand(Text &command);

	const Text &getName() const;

	const Text &getPath() const;

	const Text &getImfPath() const;

	const Text &getLogPath() const;

protected:

private:

	std::queue<Text> lines;

	Text name;

	Text path, imfPath, logPath;

};


#endif //OOPPROJECT_PROGRAM_H
