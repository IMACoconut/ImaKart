#pragma once

#include <Graphics/Render/ForwardRender.hpp>

#include <Graphics/Scene/Camera.hpp>
#include <Graphics/Scene/Light.hpp>

#include <Graphics/Tools/Mesh.hpp>

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

		void addMesh(Node* n) {
			m_method->registerNode(n);
			m_nodes.push_back(n);
		}

	private:
		Camera* m_camera;
		RenderMethod* m_method;
		std::vector<Node*> m_nodes;
	};
}