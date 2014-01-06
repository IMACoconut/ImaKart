#pragma once

#include <Graphics/Tools/Mesh.hpp>
#include <SFML/Graphics/Image.hpp>

namespace Graph {
	class Heightmap : public Mesh {
	public:
		Heightmap();
		virtual ~Heightmap();

		bool loadFromFile(const std::string& image);

		float offsetHeight(float x, float z);
		float realHeight(float x, float z);

		glm::vec3 offsetNormal(float x, float z);
		glm::vec3 realNormal(float x, float z);
		
	protected:
		glm::vec3* map;
		sf::Vector2<unsigned int> m_size;
	};
}