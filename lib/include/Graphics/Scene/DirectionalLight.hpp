#pragma once

#include <Graphics/Scene/Light.hpp>
#include <Graphics/Tools/Mesh.hpp>
#include <iostream>

namespace Graph {
	
	class DirectionalLight : public Light{
	public:
		DirectionalLight() : Light(), m_quad(Mesh::CreateQuad()) {

		}

		void draw() 
		{
			m_quad.update();
			Render::shader->send(Shader::Uniform_Vector3f, "lightDir", glm::value_ptr(position));
			Render::shader->send(Shader::Uniform_Vector3f, "lightColor", glm::value_ptr(m_color));
			Render::shader->send(Shader::Uniform_Float, "lightIntensity", &m_intensity);
			glm::mat4 id;
			Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(id));
			Render::shader->send(Shader::Uniform_Matrix4f, "viewMatrix", glm::value_ptr(id));
			Render::shader->send(Shader::Uniform_Matrix4f, "projMatrix", glm::value_ptr(id));
			m_quad.render();
			//std::cout << "lightPos" << position.x << " " << position.y << " " << position.z << std::endl;
		}

		Graph::Mesh& getMesh() {
			return m_quad;
		}
	
	private:
		Graph::Mesh m_quad;
	};

}