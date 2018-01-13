#ifndef OOPPROJECT_PROGRAM_H
#define OOPPROJECT_PROGRAM_H


#include "../Utils/utils.h"

/**
 * @brief Converts a text file containing a program and turns it into a list of
 * strings.
 */

class Program {

public:

	/**
	 * @brief Default constructor.
	 */
	Program() = default;

	/**
	 * @brief Reads a program from a file.
	 * @param programPath path to the file that should be red
	 */
	virtual void readProgram(Text programPath);

	/**
	 * @brief Retrieves a line of code.
	 * @param command string to store the result to
	 * @return false if all commands were read
	 */
	virtual bool nextCommand(Text &command);

	/**
	 * @brief Moves the command pointer to a different line
	 * @param line index of the line te move the pointer to
	 */
	virtual void seek(size_t line);

	const Text &getName() const;

	const Text &getPath() const;

	const Text &getImfPath() const;

	const Text &getLogPath() const;

private:

	// Converted lines of code
	std::vector<Text> lines;

	// Name of the program (usually acquired from the programPath)
	Text name;

	// Path to the file containing the program
	Text path;

	// Path to the intermediary file
	Text imfPath;

	// Path to the log file
	Text logPath;

	// Index of the next line to be read
	size_t pointer;

};


#endif //OOPPROJECT_PROGRAM_H
