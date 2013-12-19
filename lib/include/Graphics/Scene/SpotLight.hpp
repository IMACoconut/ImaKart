#pragma once

#include <Graphics/Scene/Light.hpp>
#include <Graphics/Tools/Mesh.hpp>
#include <iostream>
#include <glm/gtx/vector_angle.hpp>

namespace Graph {
	
	class SpotLight : public Light{
	public:
		SpotLight() : 
			Light(LightType_Spot), m_cone(Mesh::createCone(sf::Color(255,255,255,255))), m_dir(0,-100*16,0), m_radius(200) {
			setScale(glm::vec3(200,100*16,200));
			setRotation(glm::vec3(180,0,0));
			setIntensity(1.f);
			//m_cone.getMeshBuffer(0)->setDrawMode(DrawMode::Wireframe);
		}

		void draw() 
		{
			auto mat = getModelMatrix();
			Render::shader->send(Shader::Uniform_Vector3f, "lightPos", glm::value_ptr(position));
			Render::shader->send(Shader::Uniform_Vector3f, "lightDir", glm::value_ptr(m_dir));
			Render::shader->send(Shader::Uniform_Vector3f, "lightColor", glm::value_ptr(m_color));
			Render::shader->send(Shader::Uniform_Float, "lightIntensity", &m_intensity);
			Render::shader->send(Shader::Uniform_Float, "lightRadius", &m_radius);
			Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(mat));
			m_cone.render();
			//std::cout << "lightPos" << position.x << " " << position.y << " " << position.z << std::endl;
		}

		void setDirection(const glm::vec3& dir) {
			m_dir = glm::normalize(dir);
			float l = glm::length(dir);
			setScale(glm::vec3(scale.x, l, scale.z));
			float angle = glm::angle(glm::normalize(dir), glm::vec3(0,1,0));
			float angle2 = 180+glm::angle(glm::normalize(dir), glm::vec3(1,0,0));
			setRotation(glm::vec3(angle2,angle,0));
		}

		void setRadius(float radius) {
			m_radius = radius;
			setScale(glm::vec3(m_radius, scale.y, m_radius));
		}

		Graph::Mesh& getMesh() {
			return m_cone;
		}
	
	private:
		Graph::Mesh m_cone;
		glm::vec3 m_dir;
		float m_radius;
	};

}