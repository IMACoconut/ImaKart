#include <Graphics/Render/DeferredRender.hpp>
#include <Graphics/Scene/Camera.hpp>
#include <Graphics/Scene/Skydome.hpp>
#include <Graphics/Tools/Mesh.hpp>
#include <Graphics/Tools/Shader.hpp>
#include <Graphics/Tools/ShaderManager.hpp>

#include <Graphics/Scene/Camera.hpp>
#include <Graphics/Scene/Light.hpp>
#include <SFML/Graphics.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace Graph {
	
DeferredRender::DeferredRender() : save(false), loaded(false) {
	m_geometry = ShaderManager::getInstance().loadShaderFromFile(
		"DFnormal", "../resources/shaders/DFbase.vert", "../resources/shaders/DFnormal.frag");

	VertexBuffer buff;
	buff.addVertex(Vertex3D(glm::vec3(-1,-1,0),glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(255,255,255,1)));
	buff.addVertex(Vertex3D(glm::vec3(-1,1,0),glm::vec3(0,0,0), glm::vec2(0,1), sf::Color(255,255,255,1)));
	buff.addVertex(Vertex3D(glm::vec3(1,1,0),glm::vec3(0,0,0), glm::vec2(1,1), sf::Color(255,255,255,1)));
	buff.addVertex(Vertex3D(glm::vec3(1,-1,0),glm::vec3(0,0,0), glm::vec2(1,0), sf::Color(255,255,255,1)));
	buff.addTriangle(sf::Vector3i(0,1,2));
	buff.addTriangle(sf::Vector3i(0,2,3));
	m_screen.loadFromMemory(buff);
	Shader* screenShad = ShaderManager::getInstance().loadShaderFromFile(
		"DFfinal", "../resources/shaders/DFfinal.vert", "../resources/shaders/DFfinal.frag");
	m_screen.setShader(screenShad);
	m_currentBuffer = &m_gbuffer1;

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void DeferredRender::setCamera(Camera* c) {
	RenderMethod::setCamera(c);
	m_gbuffer1.clear();
	m_gbuffer1.create(c->getAspect().x, c->getAspect().y);
	m_gbuffer2.clear();
	m_gbuffer2.create(c->getAspect().x, c->getAspect().y);
	loaded = true;
}

void DeferredRender::doRender() {
	m_currentBuffer->bind(GL_DRAW_FRAMEBUFFER);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	geometryPass();
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	m_currentBuffer->unbind(GL_DRAW_FRAMEBUFFER);
	m_currentBuffer->bind(GL_READ_FRAMEBUFFER);
	//m_currentBuffer->unbind(GL_FRAMEBUFFER);
	renderScreen();
	m_currentBuffer->unbind(GL_READ_FRAMEBUFFER);
	if(m_currentBuffer == &m_gbuffer1)
		m_currentBuffer = &m_gbuffer2;
	else
		m_currentBuffer = &m_gbuffer1;
	//lightPass();
}

void DeferredRender::geometryPass() {
    
    m_camera->draw();
    /*if(m_background) {
    	Render::setShader(m_background->getShader());
    	sendUniforms();
    	m_background->render();
    }*/
   	m_geometry->bind();
    sendUniforms();
    
	
	

	for(auto it: m_meshs) {
		if(it == nullptr)
			continue;

		Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(it->getModelMatrix()));
		
		it->render();
		//std::cout << "render " << it << std::endl;
	}
}

void DeferredRender::lightPass() {

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int WINDOW_WIDTH = m_camera->getAspect().x;
    int WINDOW_HEIGHT = m_camera->getAspect().y;
    GLsizei HalfWidth = (GLsizei)(WINDOW_WIDTH / 2.0f);
    GLsizei HalfHeight = (GLsizei)(WINDOW_HEIGHT / 2.0f);

    m_currentBuffer->setBufferTarget(GBuffer::GBUFFERTARGET_DIFFUSE);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    0, HalfHeight, HalfWidth, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    m_currentBuffer->setBufferTarget(GBuffer::GBUFFERTARGET_NORMAL);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    HalfWidth, HalfHeight, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);

}

void DeferredRender::renderScreen() {
	//Render::setShader(m_screen.getShader());
	Material* tex = m_currentBuffer->getTexture(GBuffer::GBUFFERTARGET_DIFFUSE);
	Render::setTexture(Render::DiffuseTexture, tex, 0);
	Material* tex1 = m_currentBuffer->getTexture(GBuffer::GBUFFERTARGET_NORMAL);
	Render::setTexture(Render::NormalTexture, tex1, 1);
	Material* tex2 = m_currentBuffer->getTexture(GBuffer::GBUFFERTARGET_DEPTH);
	Render::setTexture(Render::DepthTexture, tex2, 2);

	auto f = m_camera->getFrustum();
  	Render::shader->send(Shader::Uniform_Float, "Near", &f.x);
	Render::shader->send(Shader::Uniform_Float, "Far", &f.y);

	glm::mat4 id;
	Render::shader->send(Shader::Uniform_Matrix4f, "viewMatrix", glm::value_ptr(id));
	Render::shader->send(Shader::Uniform_Matrix4f, "projMatrix", glm::value_ptr(id));
	Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(id));

	if(!save && loaded) {
		m_currentBuffer->save();
		save = true;
	}

	int WINDOW_WIDTH = m_camera->getAspect().x;
    int WINDOW_HEIGHT = m_camera->getAspect().y;
    m_screen.render();

	m_currentBuffer->setBufferTarget(GBuffer::GBUFFERTARGET_DIFFUSE);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    0, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    m_currentBuffer->setBufferTarget(GBuffer::GBUFFERTARGET_NORMAL);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    WINDOW_WIDTH/2, 0, WINDOW_WIDTH, WINDOW_HEIGHT/2, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    m_currentBuffer->setBufferTarget(GBuffer::GBUFFERTARGET_DEPTH);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void DeferredRender::sendUniforms() {
	if(m_camera != nullptr) {
		Render::shader->send(Shader::Uniform_Matrix4f, "viewMatrix", glm::value_ptr(m_camera->getViewMatrix()));
		Render::shader->send(Shader::Uniform_Matrix4f, "projMatrix", glm::value_ptr(m_camera->getProjMatrix()));
		Render::shader->send(Shader::Uniform_Vector3f, "eyeDir", glm::value_ptr(m_camera->forward()));
		//std::cout << "send matrix" << std::endl;
	}

	if(m_lights.size()) {
		Render::shader->send(Shader::Uniform_Vector3f, "lightPos", glm::value_ptr(m_lights[0]->getPosition()));
		//std::cout << "send light" << std::endl;
	}
}
}