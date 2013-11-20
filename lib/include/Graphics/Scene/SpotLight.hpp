#pragma once

#include <Graphics/Scene/Light.hpp>
#include <Graphics/Tools/Mesh.hpp>
#include <iostream>
#include <glm/gtx/vector_angle.hpp>

namespace Graph {
	
	class SpotLight : public Light{
	public:
		SpotLight() : Light(LightType_Spot), m_cone(Mesh::createCone()), m_dir(0,0,0), m_radius(0) {
			setScale(glm::vec3(100,100*16,100));
		}

		void draw() 
		{
			m_cone.update();
			Render::shader->send(Shader::Uniform_Vector3f, "lightPos", glm::value_ptr(position));
			Render::shader->send(Shader::Uniform_Vector3f, "lightDir", glm::value_ptr(m_dir));
			Render::shader->send(Shader::Uniform_Vector3f, "lightColor", glm::value_ptr(m_color));
			Render::shader->send(Shader::Uniform_Float, "lightIntensity", &m_intensity);
			Render::shader->send(Shader::Uniform_Float, "lightRadius", &m_intensity);
			Render::shader->send(Shader::Uniform_Matrix4f, "modelMatrix", glm::value_ptr(getModelMatrix()));
			m_cone.render();
			//std::cout << "lightPos" << position.x << " " << position.y << " " << position.z << std::endl;
		}

		void setDirection(const glm::vec3& dir) {
			m_dir = dir;
			float l = glm::length(dir);
			setScale(glm::vec3(scale.x, l, scale.z));
			float angle = glm::angle(glm::normalize(dir), glm::vec3(0,1,0));
			float angle2 = 90+glm::angle(glm::normalize(dir), glm::vec3(0,0,1));
			setRotation(glm::vec3(0,angle,angle2));
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