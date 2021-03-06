#pragma once

#include <Graphics/Scene/Camera.hpp>

namespace Graph {
	class OrbitCamera : public Camera {
	public:
		OrbitCamera(Util::Window& window, Node* target = nullptr);
		~OrbitCamera();
		void setTarget(Node* target);

		virtual void onUpdate(float elapsed);

	protected:
		Node* m_targetNode;
		float m_minDist, m_distance, m_maxDist;

		void updateOrbit();

		void move(const glm::vec3& m);
		void rotate(float horizontal, float vertical);
		void zoom(float delta);
	};
}