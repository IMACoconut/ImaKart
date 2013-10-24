#pragma once

#include <Graphics/Mesh.hpp>
#include <SFML/Graphics/Image.hpp>

namespace Graph {
	class Heightmap : public Mesh {
	public:
		Heightmap();
		~Heightmap();

		bool loadFromFile(const std::string& image);
	protected:
		sf::Image height;
	};
}