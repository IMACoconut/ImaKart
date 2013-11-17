#pragma once

#include <Graphics/Scene/Light.hpp>
#include <Graphics/Tools/Mesh.hpp>
#include <iostream>

namespace Graph {
	
	class DirectionalLight : public Light{
	public:
		DirectionalLight() : Light(LightType_Spot), m_quad(Mesh::CreateQuad()), m_dir(0,0,0), m_radius(0) {

		}

		void draw() 
		{
			m_quad.update();
			Render::shader->send(Shader::Uniform_Vector3f, "lightPos", glm::value_ptr(position));
			Render::shader->send(Shader::Uniform_Vector3f, "lightDir", glm::value_ptr(m_dir));
			Render::shader->send(Shader::Uniform_Vector3f, "lightColor", glm::value_ptr(m_color));
			Render::shader->send(Shader::Uniform_Float, "lightIntensity", &m_intensity);
			Render::shader->send(Shader::Uniform_Float, "lightRadius", &m_intensity);
			m_quad.render();
			//std::cout << "lightPos" << position.x << " " << position.y << " " << position.z << std::endl;
		}

		void setDirection(const glm::vec3& dir) {
			m_dir = dir;
		}

		void setRadius(float radius) {
			m_radius = radius;
		}

		Graph::Mesh& getMesh() {
			return m_quad;
		}
	
	private:
		Graph::Mesh m_quad;
		glm::vec3 m_dir;
		float m_radius;
	};

}