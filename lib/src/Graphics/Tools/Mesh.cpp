#include <Graphics/Tools/Mesh.hpp>
#include <Graphics/Tools/MeshLoader.hpp>

#include <Graphics/Geometry/MeshBuffer.hpp>

namespace Graph {

Mesh::Mesh(Node* parent) :
	Node(parent)
{
}

Mesh::~Mesh() {
	for(auto b: m_buffers)
		b->drop();

	m_buffers.clear();
}

Mesh::Mesh(const Mesh& other) : Node(nullptr) {
	position = other.position;
	scale = other.scale;
	rotation = other.rotation;
	for(auto b: other.m_buffers) {
		b->grab();
		m_buffers.push_back(b);
	}
}

bool Mesh::loadFromFile(const std::string& file)
{
	return MeshLoader::load3Ds(file, this);
}

bool Mesh::loadFromMemory(const VertexBuffer& buffer)
{
	MeshBuffer* m = new MeshBuffer();
	m->loadFromMemory(buffer);
	m_buffers.push_back(m);

	return true;
}

void Mesh::draw() {
	for(auto b : m_buffers)
		b->draw();
}

Mesh Mesh::CreateSphere() {
	VertexBuffer buff;
	const int seg = 16;
	const float R = 1.f/(seg-1);
	//buff.addVertex(Vertex3D(glm::vec3(0,-1,0), glm::vec3(0,-1,0), glm::vec2(0,0), sf::Color(0,0,0)));
	for(int i = 0; i<seg; ++i) {
		for(int j = 0; j<seg; ++j) {
			float x = cos(2*M_PI*j*R)*sin(M_PI*i*R);
			float y = sin(-M_PI_2+M_PI*i*R);
			float z = sin(2*M_PI*j*R)*sin(M_PI*i*R);
			buff.addVertex(Vertex3D(glm::vec3(x,y,z), glm::vec3(x,y,z), glm::vec2(0,0), sf::Color(255,0,0)));
		}
	}
	//buff.addVertex(Vertex3D(glm::vec3(0,1,0), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color(0,0,0)));
	
	/*for(int i = 1; i<seg+1; ++i) {
		buff.addTriangle(sf::Vector3i(0,i,i+1));
	}*/
	for(int i = 0; i<seg; ++i)
		for(int j = 0; j<seg; ++j) {
			buff.addTriangle(sf::Vector3i(i*seg+j,i*seg+j+1,(i+1)*seg+j));
			buff.addTriangle(sf::Vector3i(i*seg+j+1,(i+1)*seg+j+1, (i+1)*seg+j));
		}

	int toppoint = buff.getVerticesCount();
	/*for(int i = 0; i<seg; ++i) {
		buff.addTriangle(sf::Vector3i(toppoint,toppoint-i-1,toppoint-i-2));
	}*/

	Mesh m;
	m.loadFromMemory(buff);
	return m;
}

Mesh Mesh::CreateQuad() {
	VertexBuffer buff;
	buff.addVertex(Vertex3D(glm::vec3(-1,-1,0), glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(0,0,0)));
	buff.addVertex(Vertex3D(glm::vec3(1,-1,0), glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(0,0,0)));
	buff.addVertex(Vertex3D(glm::vec3(1,1,0), glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(0,0,0)));
	buff.addVertex(Vertex3D(glm::vec3(-1,1,0), glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(0,0,0)));
	buff.addTriangle(sf::Vector3i(0,1,2));
	buff.addTriangle(sf::Vector3i(0,2,3));
	Mesh m;
	m.loadFromMemory(buff);
	return m;
}
}