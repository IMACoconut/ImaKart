#pragma once 

#include <Graphics/Vertex.hpp>
#include <Graphics/VBO.hpp>
#include <Graphics/VAO.hpp>
#include <Graphics/IBO.hpp>

namespace Graph {
	class MeshBuffer {
	public:
		MeshBuffer() = default;
		bool loadFromMemory(const VertexBuffer& buffer);

		void draw();
	private:
		VertexBuffer m_buffer;
		VBO m_vbo;
		VBO m_ibo;
		VAO m_vao;
	};
}