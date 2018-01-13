#include "BadExpressionException.h"

BadExpressionException::BadExpressionException(
		const Text &msg, Exception *causedBy) : Exception(msg, causedBy) {
}
