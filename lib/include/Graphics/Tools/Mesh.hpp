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
			Mesh(const Mesh&& other);
			Mesh& operator=(const Mesh& other);

			virtual bool loadFromFile(const std::string& name);
			bool loadFromMemory(const VertexBuffer& buffer);

			void draw();

			virtual void computeBoundingBox();
			virtual void computeBoundingSphere();

			MeshBuffer* getMeshBuffer(size_t at) const;
			const std::vector<MeshBuffer*>& getMeshBuffersArray();

			static Mesh CreateSphere(const sf::Color& color);
			static Mesh CreateQuad(const sf::Color& color);
			static Mesh CreateSquare(const sf::Color& color);
			static Mesh createCone(const sf::Color& color);
			static Mesh CreateAxis();
		protected:
			std::vector<MeshBuffer*> m_buffers;

	};
}