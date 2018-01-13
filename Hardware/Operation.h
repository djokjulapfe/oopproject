#ifndef OOPPROJECT_IOPERATION_H
#define OOPPROJECT_IOPERATION_H


#include "../Utils/Interfaces.h"
#include <memory>
class Visitor;
class Token;

class Operation : public ITimedOperation {

	/**
	 * @brief Main model element.
	 */

public:

	/**
	 * @brief Auxiliary notification method.
	 * @param id of the operation notifinf
	 */
	void notify(ID id) override;

	/**
	 * @brief Accept method of the Visitor design pattern
	 * @param visitor
	 */
	virtual void accept(Visitor *visitor) = 0;

	/**
	 * @brief Does the operation it is designed for
	 */
	virtual void process() = 0;

	const Text &getName() const;

	const Text &getDescription() const;

	void setDescription(const Text &description);

	virtual void addTarget(size_t idx, Operation *operation);

	/**
	 * @brief Accepts a token and creates an event if all tokens ar ready
	 * @param idx index of the port the event is going to
	 * @param token token that is being sent
	 */
	virtual void acceptToken(size_t idx, std::shared_ptr<Token> token);

	/**
	 * @brief Checks if all tokens have arrived to input ports.
	 * @return true if all tokens have arrived
	 */
	virtual bool allTokensAccepted();

	/**
	 * @brief Sends the result token to all of it's targets
	 */
	virtual void send();

protected:

	/**
	 * @brief Default constructor.
	 * @param inputPortSize number of input ports
	 * @param name name of the operation
	 */
	explicit Operation(size_t inputPortSize, Text name = "Unnamed Operation");

	// List of tokens that ar at an operation's input, nullptr if there is no
	// token on the input
	std::vector<std::shared_ptr<Token>> inputPorts;

	// Token representing the result of the operation
	std::shared_ptr<Token> result;

	// TODO: try using weak_ptr instead of *
	// Targets the result should be sent to for later processing
	std::vector<std::pair<size_t, Operation *>> targets;


private:

	// Name of the operation
	Text name;

	// Description of the operation
	Text description;

	friend void test1();
};


#endif //OOPPROJECT_IOPERATION_H
