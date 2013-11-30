#pragma once

#include <string>
#include <sstream>

#include <SFML/Graphics/Image.hpp>

#define EPSILON 0.00001f

namespace Util {
	template <class T> inline std::string ToString(T val) {
		std::ostringstream oss;
		oss << val;
		return oss.str();
	}

	template <class T> inline T FromString(const std::string& str) {
		std::istringstream iss(str);
		T t;
		iss >> t;	
		return t;
	}

	inline sf::Color FloatToColor(float r, float g, float b, float a) {
		return sf::Color(static_cast<char>(r*255), static_cast<char>(g*255), static_cast<char>(b* 255), static_cast<char>(a *255));
	}

	inline bool eqZero(float f) {
		return std::fabs(f) < EPSILON;
	}
}