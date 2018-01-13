#include "NameCollisionException.h"

NameCollisionException::NameCollisionException(
		const Text &msg, Exception *causedBy)
		: ModelException(msg, causedBy) {
}
