#include "VarNotAvailableException.h"

VarNotAvailableException::VarNotAvailableException(
		const Text &msg, Exception *causedBy)
		: MemoryException(msg, causedBy) {
}
