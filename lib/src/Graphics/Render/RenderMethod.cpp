#include <Graphics/Render/RenderMethod.hpp>
#include <Graphics/Light.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Camera.hpp>

namespace Graph {

RenderMethod::RenderMethod() : 
	m_camera(nullptr) 
{}

void RenderMethod::registerLight(Light* l) {
	if(std::find(m_lights.begin(), m_lights.end(), l) == m_lights.end())
		m_lights.push_back(l);
}

void RenderMethod::unregisterLight(Light* l) {
	auto it = std::find(m_lights.begin(), m_lights.end(), l);
	if(it != m_lights.end())
		m_lights.erase(it);
}

void RenderMethod::registerMesh(Mesh* m) {
	if(std::find(m_meshs.begin(), m_meshs.end(), m) == m_meshs.end())
		m_meshs.push_back(m);
}

void RenderMethod::unregisterMesh(Mesh* m) {
	auto it = std::find(m_meshs.begin(), m_meshs.end(), m);
	if(it != m_meshs.end())
		m_meshs.erase(it);
}

void RenderMethod::setCamera(Camera* c) {
	m_camera = c;
}

}