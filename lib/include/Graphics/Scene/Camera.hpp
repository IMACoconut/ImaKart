#pragma once

#include <Graphics/Tools/Node.hpp>
#include <glm/glm.hpp>
#include <Utility/Window.hpp>

namespace Graph {
	class Camera : public Node {
	public:
		Camera(Util::Window& window, const glm::vec3& pos = glm::vec3(10,0,0));
		virtual ~Camera();

		void setFrustum(float near, float far);
		void setAspect(float width, float height);
		void setFov(float fov);
		glm::vec2 getAspect() const;
		glm::vec2 getFrustum() const;

		void update(float elapsed);

		void draw();
		void lookAt(const glm::vec3& at);

		glm::mat4 getProjMatrix() const;
		glm::mat4 getViewMatrix() const;

		Util::Window& getWindow();

		glm::vec3 forward();
		glm::vec3 backward();
		glm::vec3 left();
		glm::vec3 right();
		glm::vec3 up();
		glm::vec3 down();

		static glm::vec3 absoluteForward();
		static glm::vec3 absoluteLeft();
		static glm::vec3 absoluteUp();

	protected:
		virtual void onUpdate(float elapsed) {};

		void updateProjectionMatrix();
		void updateViewMatrix();

		Util::Window& m_window;
		glm::mat4 m_view;
		glm::mat4 m_proj;
		bool m_projDirty, m_viewDirty;
		float m_fov;
		float m_near, m_far, m_width, m_height;
		glm::vec3 m_forward, m_left, m_up, m_rotations, m_target;
	};
}