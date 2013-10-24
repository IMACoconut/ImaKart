#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace sf {
	typedef Vector3<unsigned int> Vector3ui;
}
namespace Graph {
	struct Vertex3D {
		sf::Vector3f position;
		sf::Vector3f normal;
		sf::Vector2f uv;
		sf::Color color;

		Vertex3D(const sf::Vector3f& p) :
			Vertex3D(p ,sf::Vector3f(0,0,0), sf::Vector2f(0,0), sf::Color(255,255,255,255))
		{}

		Vertex3D(const sf::Vector3f& p, const sf::Vector3f& n, const sf::Vector2f& u, const sf::Color& c) :
			position(p), normal(n), uv(u), color(c)
		{}
	};

	class VertexBuffer {
	public:
		VertexBuffer() = default;

		void addVertex(const Vertex3D& v) { 
			m_vertices.push_back(v); 
		}

		void addTriangle(const sf::Vector3ui& i) {
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

		const sf::Vector3ui* getIndicesData() const {
			return m_indices.data();
		}

	private:
		std::vector<Vertex3D> m_vertices;
		std::vector<sf::Vector3ui> m_indices;
	};
}