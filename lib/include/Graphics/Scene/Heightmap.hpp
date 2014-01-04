#pragma once

#include <Graphics/Tools/Mesh.hpp>
#include <SFML/Graphics/Image.hpp>

namespace Graph {
	class Heightmap : public Mesh {
	public:
		Heightmap();
		virtual ~Heightmap();

		bool loadFromFile(const std::string& image);

		float offsetHeight(float x, float y);
		float realHeight(float x, float y);
		
	protected:
		glm::vec3* map;
		sf::Vector2<unsigned int> m_size;
		//sf::Image heightmap;
	};
}