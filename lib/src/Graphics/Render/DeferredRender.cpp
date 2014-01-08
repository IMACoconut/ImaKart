#include <Graphics/Render/DeferredRender.hpp>
#include <Graphics/Scene/Camera.hpp>
#include <Graphics/Scene/Skydome.hpp>
#include <Graphics/Tools/Mesh.hpp>
#include <Graphics/Tools/Shader.hpp>
#include <Graphics/Tools/ShaderManager.hpp>
#include <Graphics/Geometry/MeshBuffer.hpp>

#include <Graphics/Scene/Camera.hpp>
#include <Graphics/Scene/OrthographicCamera.hpp>

#include <Graphics/Scene/Light.hpp>
#include <Graphics/Scene/PointLight.hpp>
#include <SFML/Graphics.hpp>

#include <Utility/LogManager.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace Graph {
	
DeferredRender::DeferredRender() : 
	loaded(false), m_meshBox(Mesh::CreateSquare(sf::Color(0,255,0))),
	m_meshSphere(Mesh::CreateSphere(sf::Color(0,255,0)))
 {
	m_geometry = ShaderManager::getInstance().loadShaderFromFile(
		"DFnormal", "../resources/shaders/DFbase.vert", "../resources/shaders/DFgeometry.frag");


	m_shadow = ShaderManager::getInstance().loadShaderFromFile(
		"DFShadowMap", "../resources/shaders/DFShadow.vert", "../resources/shaders/DFShadow.frag");
	m_custom = ShaderManager::getInstance().loadShaderFromFile(
		"DFCustom", "../resources/shaders/DFfinal.vert", "../resources/shaders/DFCustom.frag");
	m_currentShadowBuffer.init(1024,1024);
	m_currentShadowBuffer.createTexture(GBuffer::GBufferTarget_Depth);

	m_clear = ShaderManager::getInstance().loadShaderFromFile(
		"DFclear",	"../resources/shaders/DFbase.vert","../resources/shaders/DFclear.frag");

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

	m_meshBox.getMeshBuffer(0)->setDrawMode(DrawMode::Wireframe);
	m_meshBox.setShader(ShaderManager::getInstance().buildShader(&m_meshBox));
	m_meshSphere.getMeshBuffer(0)->setDrawMode(DrawMode::Wireframe);
	m_meshSphere.setShader(ShaderManager::getInstance().buildShader(&m_meshBox));
}

void DeferredRender::setCamera(Camera* c) {
	RenderMethod::setCamera(c);
	m_gbuffer1.init(c->getAspect().x, c->getAspect().y);
	m_gbuffer1.createTexture(GBuffer::GBufferTarget_Position);
	m_gbuffer1.createTexture(GBuffer::GBufferTarget_Albedo);
	m_gbuffer1.createTexture(GBuffer::GBufferTarget_Normal);

	m_gbuffer1light.init(c->getAspect().x, c->getAspect().y);
	m_gbuffer1light.createTexture(GBuffer::GBufferTarget_Light);

	loaded = true;
}



void DeferredRender::shadowPass() {
	
	m_currentShadowBuffer.bind(GL_DRAW_FRAMEBUFFER);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	
	m_shadow->bind();
	OrthographicCamera cam(m_camera->getWindow());
	cam.setFrustum(3000,30000);
	cam.setAspect(1024,1024);

	for(auto it: m_lights) {
		if(it == nullptr)
			continue;

		if(it->getType() == Light::LightType_Directional) {
			
			glm::vec3 lightPosition = it->getPosition();
			cam.setPosition(lightPosition);
			cam.lookAt(glm::vec3(128*16,128*16,128*16));
			cam.update(0);
			break;
			
		}
				
		
	}

		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
			);
		Render::shader->send(Shader::Uniform_Matrix4f, "depthviewMatrix", glm::value_ptr(cam.getViewMatrix()));
		Render::shader->send(Shader::Uniform_Matrix4f, "depthprojMatrix", glm::value_ptr(cam.getProjMatrix()));
		
		Render::shader->send(Shader::Uniform_Matrix4f, "biasMatrix", glm::value_ptr(biasMatrix));
		Render::shader->send(Shader::Uniform_Vector3f, "eyeDir", glm::value_ptr(cam.forward()));

		auto frustum = cam.getFrustum();
		Render::shader->send(Shader::Uniform_Float, "Near", &frustum.x);
		Render::shader->send(Shader::Uniform_Float, "Far", &frustum.y);
		auto view = cam.getAspect();
		Render::shader->send(Shader::Uniform_Float, "screenW", &view.x);
		Render::shader->send(Shader::Uniform_Float, "screenH", &view.y);

		
	
	// for(auto it: m_meshs) {		
	// 	Render::shader->send(Shader::Uniform_Matrix4f, "depthmodelMatrix", glm::value_ptr(it->getModelMatrix()));
	// 	it->render();
	// }
	for(auto it: m_meshs) {
		if(it == nullptr)
			continue;
		
		Render::shader->send(Shader::Uniform_Matrix4f, "depthmodelMatrix", glm::value_ptr(it->getModelMatrix()));
		
		it->render();
	}
	
	
	m_shadow->unbind();
	m_currentShadowBuffer.unbind(GL_DRAW_FRAMEBUFFER);

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);


	m_custom->bind();
	m_gbuffer1light.bind(GL_DRAW_FRAMEBUFFER);
   glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);	

	Material* tex = m_currentShadowBuffer.getTexture(GBuffer::GBufferTarget_Depth); //recuperation de la shadowmap
	Material* tex1 = m_gbuffer1.getTexture(GBuffer::GBufferTarget_Position); //recuperation de la texture de position
    //Material* tex2 = m_gbuffer1.getTexture(GBuffer::GBufferTarget_Normal);

    Render::setTexture(Render::DepthTexture, tex); //on balance au custom.frag
    Render::setTexture(Render::DiffuseTexture, tex1); //idem
    //Render::setTexture(Render::NormalTexture, tex2);
    Render::shader->send(Shader::Uniform_Float, "Near", &frustum.x);
	Render::shader->send(Shader::Uniform_Float, "Far", &frustum.y);

    view = m_camera->getAspect();
    
    Render::shader->send(Shader::Uniform_Float, "screenW", &view.x);
	Render::shader->send(Shader::Uniform_Float, "screenH", &view.y);
    Render::shader->send(Shader::Uniform_Matrix4f, "depthviewMatrix", glm::value_ptr(cam.getViewMatrix()));
	Render::shader->send(Shader::Uniform_Matrix4f, "depthprojMatrix", glm::value_ptr(cam.getProjMatrix()));
	Render::shader->send(Shader::Uniform_Matrix4f, "biasMatrix", glm::value_ptr(biasMatrix));

    m_screen.render();
    m_custom->unbind();
	m_gbuffer1light.unbind(GL_DRAW_FRAMEBUFFER);
	glDisable(GL_BLEND); 


}

void DeferredRender::doRender() {
	if(!loaded)
		return;
	
	//std::cout << "geometry" << std::endl;
	geometryPass();
	//backgroundPass();
	//alphaPass();
	lightPass();
	//std::cout << "alpha" << std::endl;
	alphaPass();
	// TODO: ajouter pass SSAO, MXAA
	//shadowPass();

	//std::cout << "final" << std::endl;

	renderScreen();
	//throw -1;
}

void DeferredRender::geometryPass() {
	m_gbuffer1.bind(GL_DRAW_FRAMEBUFFER);
	
	glEnable(GL_DEPTH_TEST);
	/*glDepthFunc(GL_ALWAYS);
	m_clear->bind();
	m_screen.render();
	m_clear->unbind();*/

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto it: m_meshs) {
		if(it == nullptr)
			continue;
		if(!it->getShader())
			it->setShader(ShaderManager::getInstance().buildShader(it));
		//if(Render::shader != it->getShader()) {
			it->getShader()->bind();
			sendUniforms();
		//}
		Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(it->getModelMatrix()));
		int b = static_cast<int>(it->getLightened()) ;
		Render::shader->send(Shader::Uniform_Integer, "isLightened", &b);
		Mesh* mesh = dynamic_cast<Mesh*>(it);
		if(mesh) {
			auto buffers = mesh->getMeshBuffersArray();

			auto material = mesh->getMaterials();
			for(int i = 0; i< Render::TextureChannel_Max; ++i)
				if(material[i] != nullptr)
					Render::setTexture(static_cast<Render::TextureChannel>(i), material[i]);

			for(auto b: buffers) {
				if(!b->hasAlphaBlending()) {
					b->draw();
				}
			}

			if(mesh->isDrawBoundingBoxEnabled())
			{
				m_meshBox.getShader()->bind();
				sendUniforms();
				m_meshBox.setPosition(mesh->getBoundingBox().getCenter());
				glm::vec3 size = mesh->getBoundingBox().getSize();
				size.x *= 0.5;
				size.y *= 0.5;
				size.z *= 0.5;
				m_meshBox.setScale(size);
				m_meshBox.update(0);
				Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(m_meshBox.getModelMatrix()));
				m_meshBox.getMeshBuffer(0)->draw();
				m_meshBox.getShader()->unbind();
			}
			if(mesh->isDrawBoundingSphereEnabled())
			{
				m_meshSphere.getShader()->bind();
				sendUniforms();
				m_meshSphere.setPosition(mesh->getBoundingSphere().getCenter());
				glm::vec3 size = glm::vec3(mesh->getBoundingSphere().radius()*2);
				m_meshSphere.setScale(size);
				m_meshSphere.update(0);
				Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(m_meshSphere.getModelMatrix()));
				m_meshSphere.getMeshBuffer(0)->draw();
				m_meshSphere.getShader()->unbind();	
			}
		}
	}
	m_geometry->unbind();
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	m_gbuffer1.unbind(GL_DRAW_FRAMEBUFFER);
}

void DeferredRender::lightPass() {
	m_gbuffer1light.bind(GL_DRAW_FRAMEBUFFER);
	//glClearColor(1.,1.,1.,1.);
	glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_CULL_FACE);

	if(Render::shader)
	{
		Render::shader->unbind();
		Render::shader = nullptr;
	}
	for(auto it: m_lights) {
		if(it == nullptr)
			continue;
		/*if(it->getType() == Light::LightType_Directional) 
			continue;
		*/	
		 if(Render::shader != it->getShader()) {
                        it->getShader()->bind();
                        sendUniforms();
                        Material* tex = m_gbuffer1.getTexture(GBuffer::GBufferTarget_Position);
                        Render::setTexture(Render::DiffuseTexture, tex);
                        Material* tex1 = m_gbuffer1.getTexture(GBuffer::GBufferTarget_Normal);
                        Render::setTexture(Render::NormalTexture, tex1);

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
	glDisable(GL_CULL_FACE);
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
 	m_gbuffer1light.bind(GL_READ_FRAMEBUFFER);
	m_gbuffer1light.setBufferTarget(GBuffer::GBufferTarget_Light);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    m_gbuffer1light.unbind(GL_READ_FRAMEBUFFER);

    m_gbuffer1.bind(GL_READ_FRAMEBUFFER);
	m_gbuffer1.setBufferTarget(GBuffer::GBufferTarget_Normal);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    0, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    m_gbuffer1.unbind(GL_READ_FRAMEBUFFER); 



    m_gbuffer1.bind(GL_READ_FRAMEBUFFER);
	m_gbuffer1.setBufferTarget(GBuffer::GBufferTarget_Position);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    WINDOW_WIDTH/2, 0, WINDOW_WIDTH, WINDOW_HEIGHT/2, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    m_gbuffer1.unbind(GL_READ_FRAMEBUFFER);

 		/*
 	
 	
    m_currentShadowBuffer.bind(GL_READ_FRAMEBUFFER);
    m_currentShadowBuffer.setBufferTarget(GBuffer::GBufferTarget_Depth);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                    WINDOW_WIDTH/2, 0, WINDOW_WIDTH, WINDOW_HEIGHT/2, GL_COLOR_BUFFER_BIT, GL_LINEAR);

   	m_currentShadowBuffer.unbind(GL_READ_FRAMEBUFFER); */

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
		/*if(Render::shader != it->getShader()) {
			it->getShader()->bind();
			sendUniforms();
		}*/
		Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(it->getModelMatrix()));
		

		Mesh* mesh = dynamic_cast<Mesh*>(it);
		if(mesh) {
			auto buffers = mesh->getMeshBuffersArray();

			
			auto material = mesh->getMaterials();
			for(int i = 0; i< Render::TextureChannel_Max; ++i)
				if(material[i] != nullptr)
					Render::setTexture(static_cast<Render::TextureChannel>(i), material[i]);

			for(auto b: buffers)
				if(b->hasAlphaBlending())
					b->draw();
		}
		it->render();
	}

	m_geometry->unbind();
	glDepthMask(GL_TRUE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	m_gbuffer1.unbind(GL_DRAW_FRAMEBUFFER);
}
}