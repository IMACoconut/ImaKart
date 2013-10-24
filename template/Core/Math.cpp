#include <Core/Math.hpp>

sf::Vector3f fromGLM(const glm::vec3& v) {
	return sf::Vector3f(v.x, v.y, v.z);
}

glm::vec3 fromSFML(const sf::Vector3f& v) {
	return glm::vec3(v.x, v.y, v.z);
}