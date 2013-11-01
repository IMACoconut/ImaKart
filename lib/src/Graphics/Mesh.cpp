#include <Graphics/Mesh.hpp>
#include <Graphics/MeshLoader.hpp>

#include <Graphics/MeshBuffer.hpp>

namespace Graph {

Mesh::Mesh(Node* parent) :
	Node(parent)
{
}

Mesh::~Mesh() {
	for(auto b: m_buffers)
		delete b;

	m_buffers.clear();
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

}