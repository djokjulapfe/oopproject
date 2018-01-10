#ifndef OOPPROJECT_IOPERATION_H
#define OOPPROJECT_IOPERATION_H


#include "../Utils/Interfaces.h"
class Visitor;
class Token;

class Operation : public ITimedOperation {

public:

	void notify(ID id) override = 0;

	virtual void accept(Visitor *visitor) = 0;

	// should set the result
	virtual void process() = 0;

	const Text &getName() const;

	void setName(const Text &name);

	const Text &getDescription() const;

	void setDescription(const Text &description);

	virtual void acceptToken(size_t idx, Token *token);

	virtual bool allTokensAccepted();

	virtual void send();

protected:

	explicit Operation(size_t inputPortSize);

	std::vector<Token *> inputPorts;

	Token *result;

private:

	static ID maxId;

	ID id;

	Text name;

	Text description;

	Operation *target;

	size_t targetIdx;

	friend void test1();

};


#endif //OOPPROJECT_IOPERATION_H
