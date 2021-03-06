#include <Graphics/Render/RenderMethod.hpp>
#include <Graphics/Scene/Light.hpp>
#include <Graphics/Scene/Skydome.hpp>
#include <Graphics/Scene/Camera.hpp>
#include <iostream>

namespace Graph {

RenderMethod::RenderMethod() : 
	m_camera(nullptr), m_background(nullptr)
{}

void RenderMethod::clear() {
	m_lights.clear();
	m_meshs.clear();
	m_camera = nullptr;
	m_background = nullptr;
}

void RenderMethod::registerLight(Light* l) {
	if(std::find(m_lights.begin(), m_lights.end(), l) == m_lights.end())
		m_lights.push_back(l);
}

void RenderMethod::unregisterLight(Light* l) {
	auto it = std::find(m_lights.begin(), m_lights.end(), l);
	if(it != m_lights.end())
		m_lights.erase(it);
}

void RenderMethod::registerNode(Node* m) {
	if(std::find(m_meshs.begin(), m_meshs.end(), m) == m_meshs.end())
		m_meshs.push_back(m);
	//std::cout << "added " << m << std::endl;
}

void RenderMethod::unregisterNode(Node* m) {
	auto it = std::find(m_meshs.begin(), m_meshs.end(), m);
	if(it != m_meshs.end())
		m_meshs.erase(it);
}

void RenderMethod::setBackground(Skydome* sky) {
	m_background = sky;
	if(sky)
		m_meshs.push_back(sky);
}

void RenderMethod::setCamera(Camera* c) {
	m_camera = c;
}

}
