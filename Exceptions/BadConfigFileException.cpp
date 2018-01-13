#include "BadConfigFileException.h"

BadConfigFileException::BadConfigFileException(
		const Text &msg, Exception *causedBy)
		: ModelException(msg, causedBy) {
}
