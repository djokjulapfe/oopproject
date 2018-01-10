#ifndef OOPPROJECT_IOPERATION_H
#define OOPPROJECT_IOPERATION_H


#include "../Utils/Interfaces.h"
#include <memory>
class Visitor;
class Token;

class Operation : public ITimedOperation {

public:

	~Operation();

	void notify(ID id) override = 0;

	virtual void accept(Visitor *visitor) = 0;

	// should set the result
	virtual void process() = 0;

	const Text &getName() const;

	void setName(const Text &name);

	const Text &getDescription() const;

	void setDescription(const Text &description);

	virtual void addTarget(size_t idx, Operation *operation);

	// TODO: implement this
	//virtual void removeTarget(Operation *operation);

	virtual void acceptToken(size_t idx, std::shared_ptr<Token> token);

	virtual bool allTokensAccepted();

	virtual void send();

	Time opTime;

protected:

	explicit Operation(size_t inputPortSize);

	std::vector<std::shared_ptr<Token>> inputPorts;

	std::shared_ptr<Token> result;

	std::vector<std::pair<size_t, Operation *>> targets;


private:

	static ID maxId;

	ID id;

	Text name;

	Text description;

	friend void test1();
};


#endif //OOPPROJECT_IOPERATION_H
