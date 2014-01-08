#pragma once

#include <Graphics/Scene/OrbitCamera.hpp>

namespace Graph {
	class KartCamera : public OrbitCamera {
	public:
		KartCamera(Util::Window& window, Node* target = nullptr);
		~KartCamera();
		void setTarget(Node* target);

		//
		void onUpdate(float elapsed);

	protected:
		//
		void updateOrbit();
	};
}