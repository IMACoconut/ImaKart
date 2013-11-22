#pragma once

#include <string>
#include <sstream>

#include <SFML/Graphics/Image.hpp>
#include <tinyxml2/tinyxml2.h>
#include <glm/glm.hpp>

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

	inline float getFloatFromXML(tinyxml2::XMLElement* xml, const std::string& name){
		tinyxml2::XMLElement* f = xml->FirstChildElement(name.c_str());
		if(f == nullptr){
			Util::LogManager::error("Float invalide : balise <"+name+"> manquante");
			throw 1;
		}
		return Util::FromString<float>(std::string(f->GetText()));

	}

	inline glm::vec3 getVec3FromXML(tinyxml2::XMLElement* xml, const std::string& name){
		tinyxml2::XMLElement* vec = xml->FirstChildElement(name.c_str());
		if(vec == nullptr){
			Util::LogManager::error("Vec3 invalide : balise <"+name+"> manquante");
			throw 1;
		}
		float x = getFloatFromXML(vec, "x");
		float y = getFloatFromXML(vec, "y");
		float z = getFloatFromXML(vec, "z");

		return glm::vec3(x,y,z);
	}

	inline sf::Color getColorFromXML(tinyxml2::XMLElement* xml, const std::string& name){
		tinyxml2::XMLElement* color = xml->FirstChildElement(name.c_str());
		if(color == nullptr){
			Util::LogManager::error("Couleur invalide : balise <"+name+"> manquante");
			throw 1;
		}
		float r = getFloatFromXML(color, "r");
		float g = getFloatFromXML(color, "g");
		float b = getFloatFromXML(color, "b");

		return FloatToColor(r,g,b, 0);
	}
}