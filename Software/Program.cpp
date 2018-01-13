#include <iostream>
#include <fstream>
#include <sstream>
#include "Program.h"

void Program::readProgram(Text programPath) {

	// save for future referencing
	path = programPath;
	pointer = 0;

	imfPath = path;
	size_t it = imfPath.length() - 1;
	while (imfPath[it] != '.') {
		imfPath.pop_back();
		it--;
	}
	logPath = imfPath;
	logPath.append("log");
	imfPath.append("imf");

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
			lines.push_back(line);
		}
		programFile.close();
	} else {
		std::cout << "Error opening " << programPath << std::endl;
	}
}

bool Program::nextCommand(Text &command) {
	if (!lines.empty() && pointer < lines.size()) {
		command = lines[pointer++];
		return true;
	} else return false;
}

const Text &Program::getName() const {
	return name;
}

const Text &Program::getPath() const {
	return path;
}

const Text &Program::getImfPath() const {
	return imfPath;
}

const Text &Program::getLogPath() const {
	return logPath;
}

void Program::seek(size_t line) {
	if (line < lines.size()) {
		pointer = line;
	}
}
