#pragma once

#include <Graphics/Scene/Light.hpp>
#include <Graphics/Tools/Mesh.hpp>
#include <iostream>

namespace Graph {
	
	class DirectionalLight : public Light{
	public:
		DirectionalLight() : Light(LightType_Directional), m_quad(Mesh::CreateQuad(sf::Color(255,255,255,255))) {

		}

		void draw() 
		{
			m_quad.update(0);
			Render::shader->send(Shader::Uniform_Vector3f, "lightDir", glm::value_ptr(position));
			Render::shader->send(Shader::Uniform_Vector3f, "lightColor", glm::value_ptr(m_color));
			Render::shader->send(Shader::Uniform_Float, "lightIntensity", &m_intensity);
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