#include <Graphics/Geometry/MeshBuffer.hpp>

namespace Graph {

bool MeshBuffer::loadFromMemory(const VertexBuffer& buffer) {
	m_buffer = buffer;
	
	m_vbo.bind();
	glBufferData(GL_ARRAY_BUFFER, m_buffer.getVerticesCount()*sizeof(Vertex3D), m_buffer.getVerticesData(), GL_STATIC_DRAW);
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_buffer.getIndicesCount() * sizeof(unsigned int)*3, m_buffer.getIndicesData(), GL_STATIC_DRAW);
	m_ibo.unbind(GL_ELEMENT_ARRAY_BUFFER);
	return true;
}

void MeshBuffer::draw() {
	m_vao.bind();
	m_ibo.bind(GL_ELEMENT_ARRAY_BUFFER);
	glDrawElements(GL_TRIANGLES, m_buffer.getIndicesCount()*3, GL_UNSIGNED_INT, (void*)0);
	m_ibo.unbind(GL_ELEMENT_ARRAY_BUFFER);
	m_vao.unbind();
}

}