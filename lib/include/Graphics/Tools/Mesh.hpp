#pragma once

#include <Graphics/Tools/Node.hpp>
#include <Graphics/Geometry/Vertex.hpp>

#include <string>
#include <vector>

namespace Graph {
	class MeshBuffer;

	class Mesh : public Node {
		public:
			Mesh(Node* parent = nullptr);
			virtual ~Mesh();
			Mesh(const Mesh& other);
			Mesh& operator=(const Mesh& other);

			virtual bool loadFromFile(const std::string& name);
			bool loadFromMemory(const VertexBuffer& buffer);

			void draw();

			static Mesh CreateSphere();
			static Mesh CreateQuad();
			static Mesh createCone();
		protected:
			std::vector<MeshBuffer*> m_buffers;

	};
}