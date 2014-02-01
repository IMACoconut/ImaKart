#include <Graphics/Tools/Mesh.hpp>
#include <Graphics/Tools/MeshLoader.hpp>

#include <Graphics/Geometry/MeshBuffer.hpp>
#include <iostream>

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
	*this = other;
}

Mesh::Mesh(const Mesh&& other) : Node(nullptr) {
	*this = other;
}

Mesh& Mesh::operator=(const Mesh& other) {
	position = other.position;
	scale = other.scale;
	rotation = other.rotation;
	for(auto b: other.m_buffers) {
		b->grab();
		m_buffers.push_back(b);
	}
	return *this;
}

bool Mesh::loadFromFile(const std::string& file)
{
	return MeshLoader::load(file, *this);
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

void Mesh::computeBoundingBox() {
	m_aabb = Phys::AABB3D(position);
	auto mat = getModelMatrix();
	for(MeshBuffer* b : m_buffers)
		for(const Vertex3D& v : b->getVertexBuffer().getVerticesArray()) {
			glm::vec4 p = mat*glm::vec4(v.position, 1.f);
			m_aabb.extends(glm::vec3(p.x, p.y, p.z));
		}
/*
	auto tmp = m_aabb.getCenter();
	//std::cout << "computed " << tmp.x << " " << tmp.y << " " << tmp.z << std::endl;
	tmp = m_aabb.getSize();
	//std::cout << "size: " << tmp.x << " " << tmp.y << " " << tmp.z << std::endl; 
*/}

void Mesh::computeBoundingSphere() {
	m_bsphere = Phys::BSphere(getBoundingBox().getCenter());
	auto mat = getModelMatrix();
	for(MeshBuffer* b : m_buffers)
		for(const Vertex3D& v : b->getVertexBuffer().getVerticesArray()) {
			glm::vec4 p = mat*glm::vec4(v.position, 1.f);
			m_bsphere.extends(glm::vec3(p.x, p.y, p.z));
		}

	//auto tmp = m_bsphere.getCenter();
	//std::cout << "computed " << tmp.x << " " << tmp.y << " " << tmp.z << std::endl;
	//std::cout << "radius: " << m_bsphere.radius() << std::endl; 
}

Mesh Mesh::CreateSphere(const sf::Color& color) {
	VertexBuffer buff;
	const int seg = 16;
	const float R = 1.f/(seg-1);
	//buff.addVertex(Vertex3D(glm::vec3(0,-1,0), glm::vec3(0,-1,0), glm::vec2(0,0), sf::Color(0,0,0)));
	for(int i = 0; i<seg; ++i) {
		for(int j = 0; j<seg; ++j) {
			float x = cos(2*M_PI*j*R)*sin(M_PI*i*R) /2;
			float y = sin(-M_PI_2+M_PI*i*R) /2;
			float z = sin(2*M_PI*j*R)*sin(M_PI*i*R) /2;
			buff.addVertex(Vertex3D(glm::vec3(x,y,z), glm::vec3(x,y,z), glm::vec2(0,0), color));
		}
	}
	//buff.addVertex(Vertex3D(glm::vec3(0,1,0), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color(0,0,0)));
	
	/*for(int i = 1; i<seg+1; ++i) {
		buff.addTriangle(sf::Vector3i(0,i,i+1));
	}*/
	for(int i = 0; i<seg-1; ++i)
		for(int j = 0; j<seg-1; ++j) {
			buff.addTriangle(sf::Vector3i(i*seg+j,i*seg+j+1,(i+1)*seg+j));
			buff.addTriangle(sf::Vector3i(i*seg+j+1,(i+1)*seg+j+1, (i+1)*seg+j));
		}

	
	/*for(int i = 0; i<seg; ++i) {
		buff.addTriangle(sf::Vector3i(toppoint,toppoint-i-1,toppoint-i-2));
	}*/

	Mesh m;
	m.loadFromMemory(buff);
	return m;
}

Mesh Mesh::CreateQuad(const sf::Color& color) {
	VertexBuffer buff;
	buff.addVertex(Vertex3D(glm::vec3(-1,-1,0), glm::vec3(0,0,0), glm::vec2(0,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,-1,0), glm::vec3(0,0,0), glm::vec2(1,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,1,0), glm::vec3(0,0,0), glm::vec2(1,1), color));
	buff.addVertex(Vertex3D(glm::vec3(-1,1,0), glm::vec3(0,0,0), glm::vec2(0,1), color));
	buff.addTriangle(sf::Vector3i(0,1,2));
	buff.addTriangle(sf::Vector3i(0,2,3));
	Mesh m;
	m.loadFromMemory(buff);
	return m;
}

Mesh Mesh::CreateAxis() {
	VertexBuffer buff;
	buff.addVertex(Vertex3D(glm::vec3(0,0,0), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color::Red));
	buff.addVertex(Vertex3D(glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color::Red));
	buff.addVertex(Vertex3D(glm::vec3(1,0.1,0), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color::Red));
	buff.addVertex(Vertex3D(glm::vec3(0,0,0), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color::Green));
	buff.addVertex(Vertex3D(glm::vec3(0,1,0), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color::Green));
	buff.addVertex(Vertex3D(glm::vec3(0.1,1,0), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color::Green));
	buff.addVertex(Vertex3D(glm::vec3(0,0,0), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color::Blue));
	buff.addVertex(Vertex3D(glm::vec3(0,0,1), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color::Blue));
	buff.addVertex(Vertex3D(glm::vec3(0,0.1,1), glm::vec3(0,1,0), glm::vec2(0,0), sf::Color::Blue));
	buff.addTriangle(sf::Vector3i(0,1,2));
	buff.addTriangle(sf::Vector3i(3,4,5));
	buff.addTriangle(sf::Vector3i(6,7,8));
	Mesh m;
	m.loadFromMemory(buff);
	return m;
}

Mesh Mesh::CreateSquare(const sf::Color& color) {
	VertexBuffer buff;
	buff.addVertex(Vertex3D(glm::vec3(-1,-1,-1), glm::vec3(0,0,0), glm::vec2(0,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,-1,-1), glm::vec3(0,0,0), glm::vec2(1,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,1,-1), glm::vec3(0,0,0), glm::vec2(1,1), color));
	buff.addVertex(Vertex3D(glm::vec3(-1,1,-1), glm::vec3(0,0,0), glm::vec2(0,1), color));
	buff.addTriangle(sf::Vector3i(0,1,2));
	buff.addTriangle(sf::Vector3i(0,2,3));

	buff.addVertex(Vertex3D(glm::vec3(-1,-1,1), glm::vec3(0,0,0), glm::vec2(0,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,-1,1), glm::vec3(0,0,0), glm::vec2(1,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,1,1), glm::vec3(0,0,0), glm::vec2(1,1), color));
	buff.addVertex(Vertex3D(glm::vec3(-1,1,1), glm::vec3(0,0,0), glm::vec2(0,1), color));
	buff.addTriangle(sf::Vector3i(4,5,6));
	buff.addTriangle(sf::Vector3i(4,6,7));

	buff.addVertex(Vertex3D(glm::vec3(-1,-1,-1), glm::vec3(0,0,0), glm::vec2(0,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,-1,-1), glm::vec3(0,0,0), glm::vec2(1,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,-1,1), glm::vec3(0,0,0), glm::vec2(1,1), color));
	buff.addVertex(Vertex3D(glm::vec3(-1,-1,1), glm::vec3(0,0,0), glm::vec2(0,1), color));
	buff.addTriangle(sf::Vector3i(8,9,10));
	buff.addTriangle(sf::Vector3i(8,10,11));

	buff.addVertex(Vertex3D(glm::vec3(-1,1,-1), glm::vec3(0,0,0), glm::vec2(0,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,1,-1), glm::vec3(0,0,0), glm::vec2(1,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,1,1), glm::vec3(0,0,0), glm::vec2(1,1), color));
	buff.addVertex(Vertex3D(glm::vec3(-1,1,1), glm::vec3(0,0,0), glm::vec2(0,1), color));
	buff.addTriangle(sf::Vector3i(12,13,14));
	buff.addTriangle(sf::Vector3i(12,14,15));

	buff.addVertex(Vertex3D(glm::vec3(-1,-1,-1), glm::vec3(0,0,0), glm::vec2(0,0), color));
	buff.addVertex(Vertex3D(glm::vec3(-1,1,-1), glm::vec3(0,0,0), glm::vec2(1,0), color));
	buff.addVertex(Vertex3D(glm::vec3(-1,1,1), glm::vec3(0,0,0), glm::vec2(1,1), color));
	buff.addVertex(Vertex3D(glm::vec3(-1,-1,1), glm::vec3(0,0,0), glm::vec2(0,1), color));
	buff.addTriangle(sf::Vector3i(16,17,18));
	buff.addTriangle(sf::Vector3i(16,18,19));

	buff.addVertex(Vertex3D(glm::vec3(1,-1,-1), glm::vec3(0,0,0), glm::vec2(0,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,1,-1), glm::vec3(0,0,0), glm::vec2(1,0), color));
	buff.addVertex(Vertex3D(glm::vec3(1,1,1), glm::vec3(0,0,0), glm::vec2(1,1), color));
	buff.addVertex(Vertex3D(glm::vec3(1,-1,1), glm::vec3(0,0,0), glm::vec2(0,1), color));
	buff.addTriangle(sf::Vector3i(20,21,22));
	buff.addTriangle(sf::Vector3i(20,22,23));

	Mesh m;
	m.loadFromMemory(buff);
	return m;
}


Mesh Mesh::createCone(const sf::Color& color) {
	VertexBuffer buff;
	buff.addVertex(Vertex3D(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec2(0,0), color));
	const int seg = 32;
	const float R = 1.f/(seg-1);
	//buff.addVertex(Vertex3D(glm::vec3(0,-1,0), glm::vec3(0,-1,0), glm::vec2(0,0), sf::Color(0,0,0)));
	for(int i = 0; i<seg; ++i) {
		float x = cos(2*M_PI*i*R);
		float y = 1;
		float z = sin(2*M_PI*i*R);
		buff.addVertex(Vertex3D(glm::vec3(x,y,z), glm::vec3(0,0,0), glm::vec2(0,0), color));
	}
	int tp = buff.getVerticesCount();
	buff.addVertex(Vertex3D(glm::vec3(0,1,0), glm::vec3(0,0,0), glm::vec2(0,0), color));

	for(int i = 0; i<seg; ++i)
		buff.addTriangle(sf::Vector3i(0,i,i+1));

	for(int i = 1; i<seg; ++i)
		buff.addTriangle(sf::Vector3i(tp,tp-i,tp-i-1));

	Mesh m;
	m.loadFromMemory(buff);
	return m;
}

MeshBuffer* Mesh::getMeshBuffer(size_t at) const {
	return m_buffers.at(at);
}

const std::vector<MeshBuffer*>& Mesh::getMeshBuffersArray() {
	return m_buffers;
}
}