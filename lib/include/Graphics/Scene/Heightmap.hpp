#pragma once

#include <Graphics/Tools/Mesh.hpp>
#include <SFML/Graphics/Image.hpp>

namespace Graph {
	class Heightmap : public Mesh {
	public:
		Heightmap()= default;
		virtual ~Heightmap();

		bool loadFromFile(const std::string& image);

		float offsetHeight(float x, float y);
		float realHeight(float x, float y);
		
	protected:
		sf::Image heightmap;
	};
}