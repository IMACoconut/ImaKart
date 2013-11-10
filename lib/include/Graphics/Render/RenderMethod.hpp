#pragma once

#include <vector>

namespace Graph {
	class Light;
	class Mesh;
	class Camera;
	class RenderMethod {
		public:
			RenderMethod();
			virtual ~RenderMethod() = default;
			
			void registerLight(Light* l);
			void unregisterLight(Light* l);

			void registerMesh(Mesh* m);
			void unregisterMesh(Mesh* m);

			void setCamera(Camera* c);

			virtual void doRender() = 0;

		protected:
			Camera* m_camera;
			std::vector<Light*> m_lights;
			std::vector<Mesh*> m_meshs;
	};
}