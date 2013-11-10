#include <Graphics/Render/ForwardRender.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Light.hpp>
#include <Graphics/Render/Render.hpp>
#include <Graphics/Shader.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace Graph {
void ForwardRender::doRender() {
/*	if(Render::shader != nullptr) {
		if(m_camera != nullptr) {
			Render::shader->send(Shader::Uniform_Matrix4f, "viewMatrix", glm::value_ptr(m_camera->getViewMatrix()));
			Render::shader->send(Shader::Uniform_Matrix4f, "projMatrix", glm::value_ptr(m_camera->getProjMatrix()));
			std::cout << "send matrix" << std::endl;
		}
		if(m_lights.size()) {
			Render::shader->send(Shader::Uniform_Vector3f, "lightPos", glm::value_ptr(m_lights[0]->getPosition()));
			std::cout << "send light" << std::endl;
		}
	}*/

	m_camera->draw();

	for(auto it: m_meshs) {
		if(Render::shader != it->getShader()) {
			it->getShader()->bind();
			if(m_camera != nullptr) {
				Render::shader->send(Shader::Uniform_Matrix4f, "viewMatrix", glm::value_ptr(m_camera->getViewMatrix()));
				Render::shader->send(Shader::Uniform_Matrix4f, "projMatrix", glm::value_ptr(m_camera->getProjMatrix()));
				Render::shader->send(Shader::Uniform_Vector3f, "eyeDir", glm::value_ptr(m_camera->forward()));
				//std::cout << "send matrix" << std::endl;
			}
			Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(it->getModelMatrix()));
		
			if(m_lights.size()) {
				Render::shader->send(Shader::Uniform_Vector3f, "lightPos", glm::value_ptr(m_lights[0]->getPosition()));
				//std::cout << "send light" << std::endl;
			}
		}
		
		it->render();
		//std::cout << "render " << it << std::endl;
	}
}
}