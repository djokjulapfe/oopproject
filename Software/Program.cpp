#include <iostream>
#include <fstream>
#include <sstream>
#include "Program.h"

void Program::readProgram(Text programPath) {

	size_t programNameStart = programPath.length();
	while (programNameStart >= 0 && programPath[programNameStart] != '/') {
		programNameStart--;
	}
	programNameStart++;
	size_t programNameEnd = programPath.length();
	while (programNameEnd >= 0 && programPath[programNameEnd] != '.') {
		programNameEnd--;
	}
	name = programPath.substr(programNameStart,
							  programNameEnd - programNameStart);

	std::ifstream programFile(programPath);
	std::string line;
	if (programFile.is_open()) {
		for (int i = 0; !programFile.eof(); i++) {
			std::getline(programFile, line);
			if (line[0] == '#') continue;
			lines.push(line);
		}
		programFile.close();
	} else {
		std::cout << "Error opening " << programPath << std::endl;
	}
}

bool Program::nextCommand(Text &command) {
	if (!lines.empty()) {
		command = lines.front();
		lines.pop();
		return true;
	} else return false;
}

const Text &Program::getName() const {
	return name;
}