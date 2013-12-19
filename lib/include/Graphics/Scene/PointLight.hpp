#pragma once

#include <Graphics/Scene/Light.hpp>
#include <Graphics/Tools/Mesh.hpp>
#include <iostream>

namespace Graph {
	
	class PointLight : public Light{
	public:
		PointLight() : Light(LightType_Point), m_radius(0.f), m_sphere(Mesh::CreateSphere(sf::Color(255,255,255,255))) {
			setRadius(100.f);
			//m_sphere.getMeshBuffer(0)->setDrawMode(DrawMode::Wireframe);
		}

		void draw() 
		{
			auto mat = getModelMatrix();
			
			Render::shader->send(Shader::Uniform_Vector3f, "lightPos", glm::value_ptr(position));
			Render::shader->send(Shader::Uniform_Vector3f, "lightColor", glm::value_ptr(m_color));
			Render::shader->send(Shader::Uniform_Float, "lightRadius", &m_radius);
			Render::shader->send(Shader::Uniform_Float, "lightIntensity", &m_intensity);
			Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(mat));
			m_sphere.render();
			//std::cout << "lightPos" << position.x << " " << position.y << " " << position.z << std::endl;
		}

		void setRadius(float radius)
		{
			m_radius = radius;
			setScale(glm::vec3(radius, radius, radius));
		}

		Graph::Mesh& getMesh() {
			return m_sphere;
		}
	
	private:
		float m_radius;
		Graph::Mesh m_sphere;
	};

}