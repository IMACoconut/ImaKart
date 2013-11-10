#pragma once

#include <Graphics/Camera.hpp>
#include <Graphics/Render/ForwardRender.hpp>

#include <Graphics/Light.hpp>
#include <Graphics/Mesh.hpp>

namespace Graph {
	
	class Scene {
	public:
		Scene() : m_camera(nullptr), m_method(new ForwardRender())
		{}

		~Scene() {
			delete m_method;
		}

		void setCamera(Camera* c) {
			m_camera = c;
			m_method->setCamera(c);
		}

		void render() {
			m_method->doRender();
		}

		void addLight(Light* l) {
			m_method->registerLight(l);
			m_nodes.push_back(l);
		}

		void addMesh(Mesh* m) {
			m_method->registerMesh(m);
			m_nodes.push_back(m);
		}
		

	private:
		Camera* m_camera;
		RenderMethod* m_method;
		std::vector<Node*> m_nodes;
	};
}