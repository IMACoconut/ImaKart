#pragma once

#include <Graphics/Node.hpp>
#include <Core/Math.hpp>

namespace Graph {
	class Camera : public Node {
	public:
		Camera();

		void setFrustum(float near, float far);
		void setAspect(float width, float height);
		void setFov(float fov);

		void draw();

		void move(const sf::Vector3f& m);

	private:
		void updateProjectionMatrix();
		void updateViewMatrix();

		glm::mat4 m_view;
		glm::mat4 m_proj;
		bool m_projDirty, m_viewDirty;
		float m_fov;
		float m_near, m_far, m_width, m_height;
		sf::Vector3f m_pos;
	};
}