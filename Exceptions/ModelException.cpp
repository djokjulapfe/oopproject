#include "ModelException.h"

ModelException::ModelException(const Text &msg, Exception *causedBy)
		: Exception(msg, causedBy) {
}
