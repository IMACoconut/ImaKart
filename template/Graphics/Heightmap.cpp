#include <Graphics/Heightmap.hpp>

namespace Graph {

Heightmap::~Heightmap() {}

bool Heightmap::loadFromFile(const std::string& image) {
	if(!heightmap.loadFromFile(image))
	{
		return false;
	}

	VertexBuffer buffer;
	auto size = heightmap.getSize();
	for(size_t x = 0; x<size.x; ++x)
		for(size_t y = 0; y<size.y; ++y)
			buffer.addVertex(Vertex3D(glm::vec3(x*10,heightmap.getPixel(x,y).r,y*10), glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(255,255,255,255)));

	for(size_t x = 0; x<size.x-1; ++x)
		for(size_t y = 0; y<size.y-1; ++y) {
			buffer.addTriangle(sf::Vector3i(x*size.x+y, x*size.x+y+1, (x+1)*size.x+y+1));
			buffer.addTriangle(sf::Vector3i(x*size.x+y, (x+1)*size.x+y+1, (x+1)*size.x+y));
		}

	loadFromMemory(buffer);
	return true;
}

}