#pragma once

#include <string>
#include <sstream>

namespace Util {
	template <class T> inline std::string ToString(T val) {
		std::ostringstream oss;
		oss << val;
		return oss.str();
	}
}