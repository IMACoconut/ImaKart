#include <Graphics/Render/DeferredRender.hpp>
#include <Graphics/Scene/Camera.hpp>
#include <Graphics/Scene/Skydome.hpp>
#include <Graphics/Tools/Mesh.hpp>
#include <Graphics/Tools/Shader.hpp>
#include <Graphics/Tools/ShaderManager.hpp>
#include <Graphics/Geometry/MeshBuffer.hpp>

#include <Graphics/Scene/Camera.hpp>
#include <Graphics/Scene/Light.hpp>
#include <Graphics/Scene/PointLight.hpp>
#include <SFML/Graphics.hpp>

#include <Utility/LogManager.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace Graph {
	
DeferredRender::DeferredRender() : save(false), loaded(false) {
	m_geometry = ShaderManager::getInstance().loadShaderFromFile(
		"DFnormal", "../resources/shaders/DFbase.vert", "../resources/shaders/DFgeometry.frag");

	VertexBuffer buff;
	buff.addVertex(Vertex3D(glm::vec3(-1,-1,0),glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(255,255,255,1)));
	buff.addVertex(Vertex3D(glm::vec3(-1,1,0),glm::vec3(0,0,0), glm::vec2(0,1), sf::Color(255,255,255,1)));
	buff.addVertex(Vertex3D(glm::vec3(1,1,0),glm::vec3(0,0,0), glm::vec2(1,1), sf::Color(255,255,255,1)));
	buff.addVertex(Vertex3D(glm::vec3(1,-1,0),glm::vec3(0,0,0), glm::vec2(1,0), sf::Color(255,255,255,1)));
	buff.addTriangle(sf::Vector3i(0,1,2));
	buff.addTriangle(sf::Vector3i(0,2,3));
	m_screen.loadFromMemory(buff);
	m_final = ShaderManager::getInstance().loadShaderFromFile(
		"DFfinal", "../resources/shaders/DFfinal.vert", "../resources/shaders/DFfinal.frag");
}

void DeferredRender::setCamera(Camera* c) {
	RenderMethod::setCamera(c);
	m_gbuffer1.init(c->getAspect().x, c->getAspect().y);
	m_gbuffer1.createTexture(GBuffer::GBufferTarget_Position);
	m_gbuffer1.createTexture(GBuffer::GBufferTarget_Albedo);
	m_gbuffer1.createTexture(GBuffer::GBufferTarget_Normal);
	m_gbuffer1.createTexture(GBuffer::GBufferTarget_Depth);

	m_gbuffer1light.init(c->getAspect().x, c->getAspect().y);
	m_gbuffer1light.createTexture(GBuffer::GBufferTarget_Light);

	loaded = true;
}

void DeferredRender::doRender() {
	
	
	
	geometryPass();
	//backgroundPass();
	alphaPass();
	lightPass();
	// TODO: ajouter pass SSAO, MXAA



	renderScreen();
}

void DeferredRender::geometryPass() {
	m_gbuffer1.bind(GL_DRAW_FRAMEBUFFER);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  
   	m_geometry->bind();
    sendUniforms();
 	

	for(auto it: m_meshs) {
		if(it == nullptr)
			continue;

		Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(it->getModelMatrix()));
		
		auto buffers = it->getMeshBuffersArray();

		
		auto material = it->getMaterials();
		for(int i = 0; i< Render::TextureChannel_Max; ++i)
			if(material[i] != nullptr)
				Render::setTexture(static_cast<Render::TextureChannel>(i), material[i]);

		for(auto b: buffers)
			if(!b->hasAlphaBlending())
				b->draw();
//		it->render();
	}

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	m_gbuffer1.unbind(GL_DRAW_FRAMEBUFFER);
}

void DeferredRender::lightPass() {
	m_gbuffer1light.bind(GL_DRAW_FRAMEBUFFER);
	glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);	

	for(auto it: m_lights) {
		if(it == nullptr)
			continue;

		if(Render::shader != it->getShader()) {
			it->getShader()->bind();
			sendUniforms();
			Material* tex = m_gbuffer1.getTexture(GBuffer::GBufferTarget_Position);
			Render::setTexture(Render::DiffuseTexture, tex);
			Material* tex1 = m_gbuffer1.getTexture(GBuffer::GBufferTarget_Normal);
			Render::setTexture(Render::NormalTexture, tex1);
			Material* tex2 = m_gbuffer1.getTexture(GBuffer::GBufferTarget_Albedo);
			Render::setTexture(Render::AmbiantTexture, tex2);
			if(it->getType() == Light::LightType_Directional) {
				glm::mat4 id;
				Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(id));
				Render::shader->send(Shader::Uniform_Matrix4f, "viewMatrix", glm::value_ptr(id));
				Render::shader->send(Shader::Uniform_Matrix4f, "projMatrix", glm::value_ptr(id));
			}
		}

		it->render();
	}

	m_gbuffer1light.unbind(GL_DRAW_FRAMEBUFFER);
	glDisable(GL_BLEND);

}

void DeferredRender::renderScreen() {
	m_final->bind();
	Material* tex = m_gbuffer1.getTexture(GBuffer::GBufferTarget_Albedo);
	Render::setTexture(Render::DiffuseTexture, tex);
	Material* tex1 = m_gbuffer1light.getTexture(GBuffer::GBufferTarget_Light);
	Render::setTexture(Render::NormalTexture, tex1);

	/*if(!save && loaded) {
		m_gbuffer1.save();
		save = true;
	}*/
    m_screen.render();
 
 	int WINDOW_WIDTH = m_camera->getAspect().x;
 	int WINDOW_HEIGHT = m_camera->getAspect().y;
 	m_gbuffer1.bind(GL_READ_FRAMEBUFFER);
	m_gbuffer1.setBufferTarget(GBuffer::GBufferTarget_Normal);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    m_gbuffer1.unbind(GL_READ_FRAMEBUFFER);
    m_gbuffer1light.bind(GL_READ_FRAMEBUFFER);
    m_gbuffer1light.setBufferTarget(GBuffer::GBufferTarget_Light);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    WINDOW_WIDTH/2, 0, WINDOW_WIDTH, WINDOW_HEIGHT/2, GL_COLOR_BUFFER_BIT, GL_LINEAR);
   	m_gbuffer1light.unbind(GL_READ_FRAMEBUFFER);
}

void DeferredRender::sendUniforms() {
	if(m_camera != nullptr) {
		Render::shader->send(Shader::Uniform_Matrix4f, "viewMatrix", glm::value_ptr(m_camera->getViewMatrix()));
		Render::shader->send(Shader::Uniform_Matrix4f, "projMatrix", glm::value_ptr(m_camera->getProjMatrix()));
		Render::shader->send(Shader::Uniform_Vector3f, "eyeDir", glm::value_ptr(m_camera->forward()));
		auto frustum = m_camera->getFrustum();
		Render::shader->send(Shader::Uniform_Float, "Near", &frustum.x);
		Render::shader->send(Shader::Uniform_Float, "Far", &frustum.y);
		auto view = m_camera->getAspect();
		Render::shader->send(Shader::Uniform_Float, "screenW", &view.x);
		Render::shader->send(Shader::Uniform_Float, "screenH", &view.y);
	}
}

void DeferredRender::backgroundPass() {
	if(m_background) {
    	Render::setShader(m_background->getShader());
    	sendUniforms();
    	Render::shader->send(Shader::Uniform_Vector3f, "lightPos", glm::value_ptr(m_lights[0]->getPosition()));
    	m_background->render();
    }
}
void DeferredRender::alphaPass() {
	m_gbuffer1.bind(GL_DRAW_FRAMEBUFFER);
   	glEnable(GL_DEPTH_TEST);
   	glDepthMask(GL_FALSE);
   	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

   	m_geometry->bind();
    sendUniforms();
 	

	for(auto it: m_meshs) {
		if(it == nullptr)
			continue;

		Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(it->getModelMatrix()));
		
		auto buffers = it->getMeshBuffersArray();

		
		auto material = it->getMaterials();
		for(int i = 0; i< Render::TextureChannel_Max; ++i)
			if(material[i] != nullptr)
				Render::setTexture(static_cast<Render::TextureChannel>(i), material[i]);

		for(auto b: buffers)
			if(b->hasAlphaBlending())
				b->draw();
//		it->render();
	}
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	m_gbuffer1.unbind(GL_DRAW_FRAMEBUFFER);
}
}