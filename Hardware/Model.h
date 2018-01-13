#ifndef OOPPROJECT_MODEL_H
#define OOPPROJECT_MODEL_H


#include "Operation.h"

class Model {

	/**
	 * @brief Main class for managing operations and their proporties
	 */

public:

	/**
	 * @brief deletes all operations that are within the Model
	 */
	~Model();

	/**
	 * @brief Singleton design pattern.
	 * @return pointer to the instance
	 */
	static Model *Instance();

	/**
	 * @brief Retrieves a operation with a given name.
	 * @param name name of the operation to be retrieved
	 * @return operation with the given name, nullptr if it doesn't exist
	 */
	static Operation *operation(const Text &name);

	/**
	 * @brief Adds a new operation to the model.
	 * @param operation opreation te be added
	 */
	virtual void add(Operation *operation);

	/**
	 * @brief Removes an operation from the model.
	 * @param operation opreation to be removed
	 */
	virtual void remove(Operation *operation);

	/**
	 * @brief Removes all opreations.
	 */
	virtual void clear();

	/**
	 * @brief Loads a .cfg file and updates Model parameters
	 * @param confPath path to the .cfg file
	 */
	virtual void loadConfig(Text confPath);

	/**
	 * @brief Retrieves a operation with a given name.
	 * @param name name of the operation to be retrieved
	 * @return operation with the given name, nullptr if it doesn't exist
	 */
	virtual Operation *findByName(const Text &name);

	Time Ts, Tm, Te, Mw, Mr;
	size_t Nw, Nr;

protected:


	/**
	 * @brief Default constructor.
	 */
	Model();

private:

	// List of operations contained within the Model
	std::vector<Operation *> operations;
};


#endif //OOPPROJECT_MODEL_H
