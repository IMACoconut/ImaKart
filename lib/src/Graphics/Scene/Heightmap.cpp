#include <Graphics/Scene/Heightmap.hpp>
#include <iostream>

namespace Graph {
Heightmap::Heightmap() : 
	map(nullptr) {

}

Heightmap::~Heightmap() {
	delete[] map;
}

	bool Heightmap::loadFromFile(const std::string& image) {
		delete[] map;
		map = nullptr;
		sf::Image heightmap;
		if(!heightmap.loadFromFile(image))
		{
			return false;
		}

		VertexBuffer buffer;
		auto size = heightmap.getSize();// - sf::Vector2<unsigned int>(1,1);
		map = new glm::vec3[size.x*size.y];
		m_size = size;
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
				v[3] = x*size.x+ym1;
				v[4] = x*size.x+yp1;
				v[5] = xp1*size.x+ym1;
				v[6] = xp1*size.x+y;
				v[7] = xp1*size.x+yp1;
				v[8] = x*size.x+y;
				for(int i = 0; i<9; ++i)
					sum += buffer.getVertex(v[i]).position.y;

				buffer2.getVertex(x*size.x+y).position.y = sum/9.f;
				map[x*m_size.x+y] = buffer2.getVertex(x*size.x+y).position;
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

		// Cinquième passe: on normalise le vecteur normal -> On ne la fait pas car le shader s'en occupe
		/*for(size_t x = 0; x<size.x-1; ++x)
			for(size_t y = 0; y<size.y-1; ++y)
				buffer2.getVertex(x*(size.x-1)+y-1).normal = glm::normalize(buffer2.getVertex(x*(size.x-1)+y-1).normal);
		*/
		std::vector<sf::Vector3i> indices = buffer.getIndicesArray();
		std::vector<Vertex3D> vertices = buffer.getVerticesArray();
		std::vector<btVector3> vertices2;
		std::vector<int> indices2;

		for(sf::Vector3i i: indices) {
		Vertex3D v1 = vertices[i.x];

		vertices2.push_back( btVector3(v1.position.x, v1.position.y, v1.position.z) );

		indices2.push_back(i.x); indices2.push_back(i.y); indices2.push_back(i.z);

		// là v1 v2 et v3 c'est les 3 vertices de ton triangle
		}


       //vertices.push_back(btVector3(v.X, v.Y, v.Z));
 
    btTriangleIndexVertexArray* vertexArray;
	vertexArray = new btTriangleIndexVertexArray(indices2.size()/3, &indices2[0], sizeof(int)*3, vertices2.size(), &vertices2[0][0], sizeof(btVector3));
	btBvhTriangleMeshShape* shape = new btBvhTriangleMeshShape(vertexArray, true);
        


		loadFromMemory(buffer2);

		//std::cout << "hend" << std::endl;
		return true;
	}

	float Heightmap::offsetHeight(float x, float y) {
		int offx = static_cast<int>(x);
		int offy = static_cast<int>(y);
		auto size = m_size;
		//std::cout << offx << " " << offy << " " << size.x << " " << size.y << std::endl;
		if(offx < 0 || offx >= (int)size.x || offy < 0 || offy >= (int)size.y)
			return -1;

		/*float px = heightmap.getPixel(offx, offy).r;
		float px2 = heightmap.getPixel(offx+1, offy).r;
		float px3 = heightmap.getPixel(offx, offy+1).r;
		float px4 = heightmap.getPixel(offx+1, offy+1).r;*/
		
		float px = map[offx*size.x+offy].y;
		float px2 = map[(offx+1)*size.x+offy].y;
		float px3 = map[offx*size.x+offy+1].y;
		float px4 = map[(offx+1)*size.x+offy+1].y;
		float fracx = x - offx, fracy = y - offy;
		float projxnear = px2*fracx+ px*(1-fracx);
		float projxfar = px4*fracx + px3*(1-fracx);
		return projxnear*(1-fracy) + projxfar*fracy;
	}

	float Heightmap::realHeight(float x, float z) {
		return offsetHeight(x/scale.x - position.x,z/scale.z - position.z) * scale.y+position.y;
	}

	glm::vec3 Heightmap::offsetNormal(float x, float y) {
		int px = static_cast<int>(x);
		int pz = static_cast<int>(y);
		glm::vec3 offpos(x,0,y);

		glm::vec3 pos[9][4];
		pos[4][0] = glm::vec3(px, map[px*m_size.x+pz].y, pz);
		pos[4][1] = glm::vec3(px, map[px*m_size.x+pz+1].y, pz+1);
		pos[4][2] = glm::vec3(px+1, map[(px+1)*m_size.x+pz].y, pz);
		pos[4][3] = glm::vec3(px+1, map[(px+1)*m_size.x+pz+1].y, pz+1);
		glm::vec3 norm[9][2];
		norm[4][0] = glm::cross(pos[4][1]-pos[4][0], pos[4][2]-pos[4][0]);
		norm[4][1] = -glm::cross(pos[4][3]-pos[4][1], pos[4][3]-pos[4][2]);
		glm::vec3 center[9][2];
		center[4][0] = (pos[4][0]+pos[4][1]+pos[4][2])/3.f;center[4][0].y = 0;
		center[4][1] = (pos[4][1]+pos[4][2]+pos[4][3])/3.f;center[4][1].y = 0;

		glm::vec3 result;
		for(int i = 4; i<5; ++i) {
			for(int j = 0; j<2; ++j) {
				float length = glm::length(offpos-center[i][j]);
				result += norm[i][j]*length;
			}
		}

		return glm::normalize(result);
	}

	glm::vec3 Heightmap::realNormal(float x, float z) {
		return offsetNormal(x/scale.x - position.x,z/scale.z - position.z);
	}

}