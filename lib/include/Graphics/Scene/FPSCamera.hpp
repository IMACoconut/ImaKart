#pragma once

#include <Graphics/Scene/Camera.hpp>

namespace Graph {
	
class FPSCamera : public Camera{
	public:
		FPSCamera(Util::Window& window, const glm::vec3& pos, const glm::vec3& dir, float moveSpeed, float rotateSpeed);
		virtual void onUpdate(float elapsed);

	protected:
		void move(const glm::vec3& m);
		void rotate(float x, float y);

	private:
		float m_moveSpeed, m_rotateSpeed;
};

}