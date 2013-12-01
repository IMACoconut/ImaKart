#pragma once

#include <vector>

namespace Graph {
	class Light;
	class Mesh;
	class Camera;
	class Skydome;
	class RenderMethod {
		public:
			RenderMethod();
			virtual ~RenderMethod(){} ;
			
			void registerLight(Light* l);
			void unregisterLight(Light* l);

			void registerMesh(Mesh* m);
			void unregisterMesh(Mesh* m);

			void setBackground(Skydome* d);
			virtual void setCamera(Camera* c);

			virtual void doRender() = 0;

		protected:
			Camera* m_camera;
			Skydome* m_background;
			std::vector<Light*> m_lights;
			std::vector<Mesh*> m_meshs;
	};
}