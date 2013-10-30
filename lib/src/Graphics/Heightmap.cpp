#include <Graphics/Heightmap.hpp>
#include <iostream>

namespace Graph {

Heightmap::~Heightmap() {}

bool Heightmap::loadFromFile(const std::string& image) {
	if(!heightmap.loadFromFile(image))
	{
		return false;
	}

	VertexBuffer buffer;
	auto size = heightmap.getSize();// - sf::Vector2<unsigned int>(1,1);
	size.x -= 1;
	size.y -= 1;

	// Première passe: on créé les vertices de la heightmap
	for(size_t x = 0; x<size.x; ++x)
		for(size_t y = 0; y<size.y; ++y)
			buffer.addVertex(Vertex3D(glm::vec3(x,heightmap.getPixel(x,y).r,y), glm::vec3(0,0,0), glm::vec2((1.f*x)/size.x,(1.f*y)/size.y), sf::Color(255,255,255,255)));


	// Deuxième passe: on créé les triangles.
	std::vector<glm::vec3> normals;
	for(size_t x = 0; x<size.x-1; ++x)
		for(size_t y = 0; y<size.y-1; ++y) {
			buffer.addTriangle(sf::Vector3i(x*size.x+y, x*size.x+y+1, (x+1)*size.x+y+1));
			buffer.addTriangle(sf::Vector3i(x*size.x+y, (x+1)*size.x+y+1, (x+1)*size.x+y));
		}

	VertexBuffer buffer2 = buffer;

	// Troisième passe: on lisse le terrain pour éviter l'effet escalier.
	for(size_t x = 0; x < size.x; ++x)
		for(size_t y = 0; y < size.y; ++y) {
			float sum = 0;
			int v[9];
			int xm1 = x > 0 ? x-1 : x;
			int xp1 = x < (size.x-1) ? x+1 : x;
			int ym1 = y > 0 ? y-1 : y;
			int yp1 = y < (size.y-1) ? y+1 : y;

			v[0] = xm1*size.x+ym1;
			v[1] = xm1*size.x+y;
			v[2] = xm1*size.x+yp1;
			v[3] = x*size.x+xm1;
			v[4] = x*size.x+yp1;
			v[5] = xp1*size.x+ym1;
			v[6] = xp1*size.x+y;
			v[7] = xp1*size.x+yp1;
			v[8] = x*size.x+y;
			for(int i = 0; i<9; ++i)
				sum += buffer.getVertex(v[i]).position.y;

			buffer2.getVertex(x*size.x+y).position.y = sum/9.f;
		}

	// Quatrième passe: on génère les normales en chaque point (pour l'éclairage)
	for(size_t x = 0; x<size.x-1; ++x)
		for(size_t y = 0; y<size.y-1; ++y) {

			glm::vec3 p1,p2,p3, v1,v2,tmp;
			int v[4];
			v[0] = x*size.x+y;
			v[1] = x*size.x+y+1;
			v[2] = (x+1)*size.x+y;
			v[3] = (x+1)*size.x+y+1;
			p1 = buffer2.getVertex(v[0]).position;
			p2 = buffer2.getVertex(v[3]).position;
			p3 = buffer2.getVertex(v[2]).position;
			v1 = p2 - p1; v2 = p3 - p1;
			tmp = glm::cross(v1,v2);
			buffer2.getVertex(v[0]).normal += tmp;
			buffer2.getVertex(v[3]).normal += tmp;
			buffer2.getVertex(v[2]).normal += tmp;

			p1 = buffer2.getVertex(v[1]).position;
			p2 = buffer2.getVertex(v[3]).position;
			p3 = buffer2.getVertex(v[0]).position;
			v1 = p2 - p1; v2 = p3 - p1;
			tmp = glm::cross(v1,v2);
			buffer2.getVertex(v[1]).normal += tmp;
			buffer2.getVertex(v[3]).normal += tmp;
			buffer2.getVertex(v[0]).normal += tmp;
		}

	// Cinquième passe: on normalise le vecteur normal.
	for(size_t x = 0; x<size.x-1; ++x)
		for(size_t y = 0; y<size.y-1; ++y)
			buffer2.getVertex(x*size.x+y-1).normal = glm::normalize(buffer2.getVertex(x*size.x+y).normal);
	
	loadFromMemory(buffer2);
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