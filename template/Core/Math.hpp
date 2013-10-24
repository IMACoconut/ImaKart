#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

sf::Vector3f fromGLM(const glm::vec3& v);

glm::vec3 fromSFML(const sf::Vector3f& v);