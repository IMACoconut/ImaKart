#pragma once

#include <Graphics/Node.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Graph {
	class Camera : public Node {
	public:
		Camera();

		void setFrustum(float near, float far);
		void setAspect(float width, float height);
		void setFov(float fov);

		void draw();

		void move(const glm::vec3& m);
		void rotate(float horizontal, float vertical);

		glm::vec3 forward();
		glm::vec3 backward();
		glm::vec3 left();
		glm::vec3 right();
		glm::vec3 up();
		glm::vec3 down();

		static glm::vec3 absoluteForward();
		static glm::vec3 absoluteLeft();
		static glm::vec3 absoluteUp();

	private:
		void updateProjectionMatrix();
		void updateViewMatrix();

		glm::mat4 m_view;
		glm::mat4 m_proj;
		bool m_projDirty, m_viewDirty;
		float m_fov;
		float m_near, m_far, m_width, m_height;
		glm::vec3 m_pos;
		glm::vec3 m_forward;
		glm::vec3 m_left;
		glm::vec3 m_up;
		glm::vec3 m_rotations;
	};
}