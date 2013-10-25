#include <Graphics/Heightmap.hpp>

namespace Graph {

bool Heightmap::loadFromFile(const std::string& image) {
	if(!height.loadFromFile(image))
	{
		return false;
	}

	/*VertexBuffer buffer;
	auto size = height.getSize();*/
	/*for(size_t x = 0; x<size.x; ++x)
		for(size_t y = 0; y<size.y; ++y)
			buffer.addVertex(Vertex3D(sf::Vector3f(x,y,height.getPixel(x,y).r), sf::Vector3f(0,0,0), sf::Vector2f(0,0), sf::Color(255,255,255,255)));
*/
	return false;
}

}