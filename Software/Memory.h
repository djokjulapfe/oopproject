#ifndef OOPPROJECT_MEMORY_H
#define OOPPROJECT_MEMORY_H


#include <map>
#include "../Utils/types.h"

class Memory {
public:

	static Memory *Instance();

	virtual void set(Text varName, double val);

	virtual double get(Text varName);

protected:

	Memory() = default;

private:
	std::map<Text, double> mem;
};


#endif //OOPPROJECT_MEMORY_H
