#include "Exception.h"

const char *Exception::what() const noexcept {
	Text ret;
	if (causedBy != nullptr) {
		ret = causedBy->what();
		ret.append("\n caused by ");
		ret.append(msg);
	} else {
		ret = msg;
	}
	return ret.c_str();
}

Exception::Exception(const Text &msg, Exception *causedBy)
		: causedBy(causedBy), msg(msg) {
}
