#pragma once 

#include <Graphics/Geometry/Vertex.hpp>
#include <Graphics/Geometry/VBO.hpp>
#include <Graphics/Geometry/VAO.hpp>

#include <Utility/Resource.hpp>

namespace Graph {
	typedef enum {
		Point,
		Wireframe,
		Full
	} DrawMode;
	typedef enum {
		Solid,
		AlphaBlending
	} RenderMode;
	
	class MeshBuffer : public Util::Resource {
	public:

		MeshBuffer();
		bool loadFromMemory(const VertexBuffer& buffer);

		void draw();
		void setDrawMode(DrawMode m);
		void setRenderMode(RenderMode m);

		bool hasAlphaBlending() const;

		const VertexBuffer& getVertexBuffer() const;

	private:
		RenderMode m_renderMode;
		DrawMode m_drawMode;
		VertexBuffer m_buffer;
		VBO m_vbo;
		VBO m_ibo;
		VAO m_vao;
	};
}