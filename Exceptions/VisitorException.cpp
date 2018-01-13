#include "VisitorException.h"

VisitorException::VisitorException(const Text &msg, Exception *causedBy)
		: Exception(msg, causedBy) {
}
