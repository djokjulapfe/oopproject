#ifndef OOPPROJECT_TOKEN_H
#define OOPPROJECT_TOKEN_H


#include "../Utils/utils.h"
#include "Operation.h"

class Token {

	/**
	 * @brief Main objects in the flow
	 */

public:

	/**
	 * @brief User friently constructor.
	 * @param value value of the token
	 * @param name of the token
	 */
	explicit Token(double value, Text name = "Unnamed Token");

	/**
	 * @brief Default constructor.
	 */
	Token();

	double getValue() const;

	const Text &getName() const;

	void setValue(double value);

private:

	// Name of the token
	Text name;

	// Operation that produced the token
	Operation *producedBy;

public:

	// Volue of the token
	double value;

};


#endif //OOPPROJECT_TOKEN_H
