#pragma once

#include <Graphics/Tools/Node.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Graphics/Tools/Shader.hpp>
#include <Graphics/Render/Render.hpp>

namespace Graph {
	class Mesh;
	
	class Light : public Node {
	public:
		typedef enum {
			LightType_Point,
			LightType_Spot,
			LightType_Directional
		} LightType;

		Light(LightType t) : m_type(t), m_color(1,1,1), m_intensity(1) {}
		virtual void draw() = 0;

		void setColor(const glm::vec3& color) {
			m_color = color;
		}
		void setIntensity(float intensity) {
			m_intensity = intensity;
		}

		LightType getType() const {
			return m_type;
		}

		virtual Mesh& getMesh() = 0;

	protected:
		LightType m_type;
		glm::vec3 m_color;
		float m_intensity;

	};
}