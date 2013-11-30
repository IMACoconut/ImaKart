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
	void setCamera(Camera* c);
	void doRender();

protected:
	void geometryPass();
	void lightPass();
	void renderScreen();
	void sendUniforms();

	bool save, loaded;
	GBuffer m_gbuffer1, m_gbuffer1light, m_gbuffer2, m_gbuffer2light;
	GBuffer* m_currentBuffer, *m_currentLightBuffer;
	Graph::Shader *m_geometry, *m_final;
	Graph::Mesh m_screen;
};

}