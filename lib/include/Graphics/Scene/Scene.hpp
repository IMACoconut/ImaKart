#pragma once

#include <Graphics/Render/ForwardRender.hpp>
#include <Graphics/Render/DeferredRender.hpp>

#include <Graphics/Scene/Camera.hpp>
#include <Graphics/Scene/Light.hpp>
#include <Graphics/Scene/Skydome.hpp>

#include <Graphics/Tools/Mesh.hpp>

namespace Graph {
	class Scene {
	public:
		Scene() : m_camera(nullptr), m_method(new DeferredRender())
		{}

		~Scene() {
			delete m_method;
		}

		void setCamera(Camera* c) {
			m_camera = c;
			m_method->setCamera(c);
		}

		void update(float elapsed) {
			m_camera->update(elapsed);
			m_background->update(elapsed);
			for(Node* n : m_nodes)
				n->update(elapsed);
		}

		void render() {
			m_method->doRender();
		}

		void addLight(Light* l) {
			m_method->registerLight(l);
			m_nodes.push_back(l);
		}

		void addMesh(Node* n) {
			m_method->registerNode(n);
			m_nodes.push_back(n);
		}

		void setBackground(Skydome* d) {
			m_method->setBackground(d);
			m_background = d;
		}
		
	private:
		Camera* m_camera;
		Skydome* m_background;
		RenderMethod* m_method;
		std::vector<Node*> m_nodes;
	};
}