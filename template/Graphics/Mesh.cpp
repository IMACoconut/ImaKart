#include <Graphics/Mesh.hpp>
#include <Graphics/MeshLoader.hpp>

#include <Utility/LogManager.hpp>

namespace Graph {

Mesh::Mesh(Node* parent) :
	Node(parent)
{
	m_buffers.push_back(new VertexBuffer());
}

Mesh::~Mesh() {
	while(m_buffers.size()) {
		delete m_buffers.back();
		m_buffers.pop_back();
	}
}

bool Mesh::loadFromFile(const std::string& file)
{
	return MeshLoader::load3Ds(file, this);
}

bool Mesh::loadFromMemory(const VertexBuffer& buffer)
{
	*m_buffers[0] = buffer;
	
	m_vbo.bind();
	glBufferData(GL_ARRAY_BUFFER, m_buffers[0]->getVerticesCount()*sizeof(Vertex3D), m_buffers[0]->getVerticesData(), GL_STATIC_DRAW);
	m_vbo.unbind();

	m_vao.bind();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	m_vbo.bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex3D), (const GLvoid*)offsetof(Vertex3D, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex3D), (const GLvoid*)offsetof(Vertex3D, normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex3D), (const GLvoid*)offsetof(Vertex3D, uv));
	glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex3D), (const GLvoid*)offsetof(Vertex3D, color));
	m_vbo.unbind();
	m_vao.unbind();

	m_ibo.bind(GL_ELEMENT_ARRAY_BUFFER);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_buffers[0]->getIndicesCount() * sizeof(unsigned int)*3, m_buffers[0]->getIndicesData(), GL_STATIC_DRAW);
	m_ibo.unbind(GL_ELEMENT_ARRAY_BUFFER);

	return true;
}

size_t Mesh::getMeshBuffersCount() const {
	return m_buffers.size();
}
VertexBuffer* Mesh::getMeshBuffer(size_t i) {
	return m_buffers[i];
}


void Mesh::draw() {
	m_vao.bind();
	m_ibo.bind(GL_ELEMENT_ARRAY_BUFFER);
	glDrawElements(GL_TRIANGLES, m_buffers[0]->getIndicesCount()*3, GL_UNSIGNED_INT, (void*)0);
	m_ibo.unbind(GL_ELEMENT_ARRAY_BUFFER);
	m_vao.unbind();
}

}