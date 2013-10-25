#pragma once

#include <Graphics/Node.hpp>
#include <Graphics/Vertex.hpp>

#include <string>
#include <vector>

namespace Graph {
	class MeshBuffer;

	class Mesh : public Node {
		public:
			Mesh(Node* parent = nullptr);
			virtual ~Mesh();

			virtual bool loadFromFile(const std::string& name);
			bool loadFromMemory(const VertexBuffer& buffer);

			void draw();

		protected:
			std::vector<MeshBuffer*> m_buffers;

	};
}