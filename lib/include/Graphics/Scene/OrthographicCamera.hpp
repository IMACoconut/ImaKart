#pragma once

#include <Graphics/Scene/Camera.hpp>

namespace Graph {
	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(Util::Window& window, Node* target = nullptr);
		~OrthographicCamera();

		void updateProjectionMatrix();

		

	protected:
		

	private:
		Node* m_targetNode;
		float m_minDist, m_distance, m_maxDist;
	
	};
}