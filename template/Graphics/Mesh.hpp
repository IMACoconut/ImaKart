#pragma once

#include <Graphics/Node.hpp>
#include <Graphics/VBO.hpp>
#include <Graphics/VAO.hpp>
#include <Graphics/IBO.hpp>
#include <Graphics/Vertex.hpp>

#include <string>
#include <vector>

namespace Graph {
	std::vector<Vertex3D> square();

	class Mesh : public Node {
		public:
			Mesh(Node* parent = nullptr);
			virtual ~Mesh();

			virtual bool loadFromFile(const std::string& name);
			bool loadFromMemory(const VertexBuffer& buffer);

			size_t getMeshBuffersCount() const;
			VertexBuffer* getMeshBuffer(size_t i);
			void draw();

		protected:
			std::vector<VertexBuffer*> m_buffers;
			VBO m_vbo;
			VBO m_ibo;
			VAO m_vao;
	};
}