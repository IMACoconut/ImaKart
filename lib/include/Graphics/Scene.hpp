#pragma once

#include <Graphics/Camera.hpp>
#include <Graphics/Render.hpp>

namespace Graph {
	
	class Scene : public Node {
	public:
		Scene() : Node(), m_camera(nullptr)
		{}

		void setCamera(Camera* c) {
			m_camera = c;
		}

		void draw() {
			if(m_camera)
				m_camera->render();
		}

	private:
		Camera* m_camera;
	};
}