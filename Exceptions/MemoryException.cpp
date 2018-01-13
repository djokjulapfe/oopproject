#include "MemoryException.h"

MemoryException::MemoryException(const Text &msg, Exception *causedBy)
		: Exception(msg, causedBy) {
}
