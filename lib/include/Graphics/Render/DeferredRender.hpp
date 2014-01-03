#pragma once

#include <Graphics/Render/RenderMethod.hpp>
#include <Graphics/Geometry/GBuffer.hpp>
#include <Graphics/Tools/Mesh.hpp>

namespace Graph {
class Camera;
class Shader;
class DeferredRender : public RenderMethod {
public:
	DeferredRender();
	~DeferredRender() {};
	void setCamera(Camera* c);
	void doRender();

protected:
	void geometryPass();
	void backgroundPass();
	void alphaPass();
	void lightPass();
	void renderScreen();
	void sendUniforms();

	bool save, loaded;
	GBuffer m_gbuffer1, m_gbuffer1light;
	Graph::Shader *m_geometry, *m_alpha, *m_final, *m_clear;
	Graph::Mesh m_screen, m_meshBox, m_meshSphere;
};

}
