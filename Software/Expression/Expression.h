#ifndef OOPPROJECT_EXPRESSION_H
#define OOPPROJECT_EXPRESSION_H

#include "../../Utils/utils.h"

class ExpressionVisitor;
class CompositeExpression;

class Expression {

	/**
	 * @brief Realizes an expression for compiling code.
	 */

public:

	/**
	 * @brief default constructor
	 * @param name of the expression
	 */
	explicit Expression(const Text &name);

	/**
	 * @brief Virtualisation of the destructor for use in subclasses
	 */
	virtual ~Expression() = default;

	/**
	 * @brief Accept methot of the Visitor design pattern
	 * @param visitor
	 */
	virtual void accept(ExpressionVisitor *visitor) = 0;

	const Text &getName() const;

	/**
	 * @brief Used in polymorphism when checking Expression type
	 * @return true if this is an instance of CompositeExpression
	 */
	virtual bool isComposite() = 0;

protected:

	// Name of the expressino
	Text name;

};


#endif //OOPPROJECT_EXPRESSION_H
