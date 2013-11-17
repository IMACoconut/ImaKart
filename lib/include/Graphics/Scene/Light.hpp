#pragma once

#include <Graphics/Tools/Node.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Graphics/Tools/Shader.hpp>
#include <Graphics/Render/Render.hpp>

namespace Graph {
	class Light : public Node {
	public:
		virtual void draw() = 0;

		void setColor(const glm::vec3& color) {
			m_color = color;
		}
		void setIntensity(float intensity) {
			m_intensity = intensity;
		}

	protected:
		glm::vec3 m_color;
		float m_intensity;

	};
}