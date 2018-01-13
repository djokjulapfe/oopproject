#include "IndexOutOfBoundsException.h"

IndexOutOfBoundsException::IndexOutOfBoundsException(
		const Text &msg, Exception *causedBy)
		: Exception(msg, causedBy) {
}
