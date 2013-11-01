#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace Graph {
	struct Vertex3D {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
		sf::Color color;

		Vertex3D(const glm::vec3& p) :
			Vertex3D(p ,glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(255,255,255,255))
		{}

		Vertex3D(const glm::vec3& p, const glm::vec3& n, const glm::vec2& u, const sf::Color& c) :
			position(p), normal(n), uv(u), color(c)
		{}
	};

	class VertexBuffer {
	public:
		VertexBuffer() = default;

		void clear() {
			m_vertices.clear();
			m_indices.clear();
		}
		void addVertex(const Vertex3D& v) { 
			m_vertices.push_back(v); 
		}

		void addTriangle(const sf::Vector3i& i) {
			m_indices.push_back(i);
		}

		Vertex3D& getVertex(size_t i) {
			return m_vertices[i];
		}

		std::size_t getVerticesCount() const {
			return m_vertices.size();
		}

		std::size_t getIndicesCount() const {
			return m_indices.size();
		}

		const Vertex3D* getVerticesData() const {
			return m_vertices.data();
		}

		const sf::Vector3i* getIndicesData() const {
			return m_indices.data();
		}

	private:
		std::vector<Vertex3D> m_vertices;
		std::vector<sf::Vector3i> m_indices;
	};
}