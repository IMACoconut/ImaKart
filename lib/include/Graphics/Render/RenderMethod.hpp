#pragma once

#include <vector>

namespace Graph {
	class Light;
	class Node;
	class Camera;
	class Skydome;
	class RenderMethod {
		public:
			RenderMethod();
			virtual ~RenderMethod() = default;
			
			void registerLight(Light* l);
			void unregisterLight(Light* l);

			void registerNode(Node* m);
			void unregisterNode(Node* m);

			void setBackground(Skydome* d);
			virtual void setCamera(Camera* c);

			virtual void doRender() = 0;

		protected:
			Camera* m_camera;
			Skydome* m_background;
			std::vector<Light*> m_lights;
			std::vector<Node*> m_meshs;
	};
}
