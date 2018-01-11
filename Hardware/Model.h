#ifndef OOPPROJECT_MODEL_H
#define OOPPROJECT_MODEL_H


#include "Operation.h"

class Model {
public:

	~Model();

	static Model *Instance();

	static Operation *operation(const Text &name);

	virtual void add(Operation *operation);

	virtual void remove(Operation *operation);

	virtual void clear();

	virtual Operation *findByName(const Text &name);

	// TODO: make a create method

	Time Ts, Tm, Te, Mw, Mr;
	size_t Nw, Nr;

protected:

	// load a .imf file
	Model();

private:

	std::vector<Operation *> operations;
};


#endif //OOPPROJECT_MODEL_H
