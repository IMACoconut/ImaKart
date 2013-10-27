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
			buffer.addVertex(Vertex3D(glm::vec3(x,heightmap.getPixel(x,y).r,y), glm::vec3(0,0,0), glm::vec2((1.f*x)/size.x,(1.f*y)/size.y), sf::Color(255,255,255,255)));

	std::vector<glm::vec3> normals;
	for(size_t x = 0; x<size.x-1; ++x)
		for(size_t y = 0; y<size.y-1; ++y) {
			buffer.addTriangle(sf::Vector3i(x*size.x+y, x*size.x+y+1, (x+1)*size.x+y+1));
			/*normals.push_back(glm::cross(
				(buffer.getVertex((x+1)*size.x+y+1).position-buffer.getVertex(x*size.x+y).position),
				(buffer.getVertex(x*size.x+y+1).position-buffer.getVertex(x*size.x+y).position)));*/
			
			buffer.addTriangle(sf::Vector3i(x*size.x+y, (x+1)*size.x+y+1, (x+1)*size.x+y));
			/*normals.push_back(glm::cross(
				(buffer.getVertex((x+1)*size.x+y).position-buffer.getVertex(x*size.x+y).position),
				(buffer.getVertex((x+1)*size.x+y+1).position-buffer.getVertex(x*size.x+y).position)));*/
		}

	for(size_t x = 0; x<size.x-1; ++x)
		for(size_t y = 0; y<size.y-1; ++y) {

			glm::vec3 p1,p2,p3, v1,v2,tmp;
			int v[4];
			v[0] = x*size.x+y;
			v[1] = x*size.x+y+1;
			v[2] = (x+1)*size.x+y;
			v[3] = (x+1)*size.x+y+1;
			p1 = buffer.getVertex(v[0]).position;
			p2 = buffer.getVertex(v[3]).position;
			p3 = buffer.getVertex(v[2]).position;
			v1 = p2 - p1; v2 = p3 - p1;
			tmp = glm::cross(v1,v2);
			buffer.getVertex(v[0]).normal += tmp;
			buffer.getVertex(v[3]).normal += tmp;
			buffer.getVertex(v[2]).normal += tmp;

			p1 = buffer.getVertex(v[1]).position;
			p2 = buffer.getVertex(v[3]).position;
			p3 = buffer.getVertex(v[0]).position;
			v1 = p2 - p1; v2 = p3 - p1;
			tmp = glm::cross(v1,v2);
			buffer.getVertex(v[1]).normal += tmp;
			buffer.getVertex(v[3]).normal += tmp;
			buffer.getVertex(v[0]).normal += tmp;
		}
	for(size_t x = 0; x<size.x-1; ++x)
		for(size_t y = 0; y<size.y-1; ++y)
			buffer.getVertex(x*size.x+y).normal = glm::normalize(buffer.getVertex(x*size.x+y).normal);
	
	loadFromMemory(buffer);
	return true;
}

float Heightmap::offsetHeight(float x, float y) {
	int offx = static_cast<int>(x);
	int offy = static_cast<int>(y);
	auto size = heightmap.getSize();
	if(offx < 0 || offx >= static_cast<int>(size.x) || offy < 0 || offy >= static_cast<int>(size.y))
		return -1;

	float px = heightmap.getPixel(offx, offy).r;
	float px2 = heightmap.getPixel(offx+1, offy).r;
	float px3 = heightmap.getPixel(offx, offy+1).r;
	float px4 = heightmap.getPixel(offx+1, offy+1).r;

	return (px+px2+px3+px4)/4.f;
}

float Heightmap::realHeight(float x, float y) {
	return offsetHeight(x,y)+position.y;
}

}