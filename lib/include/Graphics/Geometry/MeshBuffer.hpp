#pragma once 

#include <Graphics/Geometry/Vertex.hpp>
#include <Graphics/Geometry/VBO.hpp>
#include <Graphics/Geometry/VAO.hpp>

#include <Utility/Resource.hpp>

namespace Graph {
	class MeshBuffer : public Util::Resource {
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