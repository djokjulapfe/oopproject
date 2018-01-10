#ifndef OOPPROJECT_MODEL_H
#define OOPPROJECT_MODEL_H


#include "Operation.h"

class Model {
public:

	~Model();

	static Model *Instance();

	virtual void add(Operation *operation);

	virtual void remove(Operation *operation);

	virtual void clear();

protected:

	// load a .imf file
	Model();

private:

	std::vector<Operation *> operations;
};


#endif //OOPPROJECT_MODEL_H
