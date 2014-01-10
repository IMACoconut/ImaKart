#pragma once

#include <Graphics/Render/ForwardRender.hpp>
#include <Graphics/Render/DeferredRender.hpp>

#include <Graphics/Scene/Camera.hpp>
#include <Graphics/Scene/Light.hpp>
#include <Graphics/Scene/Skydome.hpp>

#include <Graphics/Tools/Mesh.hpp>

#include <Physics/BSphere.hpp>
#include <Physics/AABB3D.hpp>

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
			if(m_camera)
				m_camera->update(elapsed);
			if(m_background)
				m_background->update(elapsed);
			for(Light* l: m_lights)
				l->update(elapsed);
			for(Node* n : m_nodes)
				n->update(elapsed);
		}

		void clear() {
			m_lights.clear();
			m_nodes.clear();
			m_background = nullptr;
			m_camera = nullptr;
			delete m_method;
			m_method = new DeferredRender();
		}

		void render() {
			m_method->doRender();
		}

		void addLight(Light* l) {
			m_method->registerLight(l);
			m_lights.push_back(l);
		}

		void addMesh(Node* n) {
			m_method->registerNode(n);
			m_nodes.push_back(n);
		}

		void setBackground(Skydome* d) {
			m_method->setBackground(d);
			m_background = d;
		}

		glm::vec3 getCenter() {
			auto aabb = computeBoundingBox();
			return aabb.getCenter();
		}

		Phys::BSphere computeBoundingSphere() {
			auto center = getCenter();
			Phys::BSphere sphere(center);
			for(Node* n: m_nodes)
				sphere.extends(n->getBoundingSphere());
			return sphere;
		}

		Phys::AABB3D computeBoundingBox() {
			Phys::AABB3D box;
			for(Node* n: m_nodes)
				box.extends(n->getBoundingBox());
			return box;
		}
		
	private:
		Camera* m_camera;
		Skydome* m_background;
		RenderMethod* m_method;
		std::vector<Node*> m_nodes;
		std::vector<Light*> m_lights;
	};
}