#include <Graphics/Scene/OrbitCamera.hpp>
#include <Utility/Input/XboxInput.hpp>
#include <Utility/Input/MouseInput.hpp>
#include <iostream>
#include <cmath>

namespace Graph {

OrbitCamera::OrbitCamera(Util::Window& window, Node* target) : 
	Camera(window),
	m_targetNode(target), 
	m_minDist(50.f), 
	m_distance(500.f), 
	m_maxDist(5000.f) 
{

}

OrbitCamera::~OrbitCamera() {}

void OrbitCamera::onUpdate(float elapsed) {
	
	if(m_window.getXbox().isConnected(0))
	{
		auto rsaxis = m_window.getXbox().getAxis(0, Util::XboxAxis::RStick);
		float rtrigg = m_window.getXbox().getTrigger(0, Util::XboxTrigger::RT);
		float ltrigg = m_window.getXbox().getTrigger(0, Util::XboxTrigger::LT);

		if(!Util::eqZero(rtrigg)) {
			zoom(elapsed*-5.f);
		}
		if(!Util::eqZero(ltrigg)) {
			zoom(elapsed*5.f);
		}

		rotate(rsaxis.x*elapsed*5, rsaxis.y*elapsed*5);
	}
	auto move = m_window.getMouse().getMouseDelta();
	float wheel = m_window.getMouse().getWheelDelta();
	zoom(wheel*elapsed*5.f);
	rotate(move.x*elapsed, move.y*elapsed);
	updateOrbit();
	
}

void OrbitCamera::move(const glm::vec3& m) {}
void OrbitCamera::rotate(float dx, float dy) {
	m_rotations.y -= dx*0.005f*5;
	m_rotations.x += dy*0.005f*5;

	if(m_rotations.x < -179.f)
		m_rotations.x = -179.f;
	else if(m_rotations.x > -1.f)
		m_rotations.x = -1.f;
}
void OrbitCamera::zoom(float delta) {
	m_distance += delta;
	if(m_distance > m_maxDist)
		m_distance = m_maxDist;
	else if(m_distance < m_minDist)
		m_distance = m_minDist;
}

void OrbitCamera::setTarget(Node* target) {
	m_targetNode = target;
	updateOrbit();
}

void OrbitCamera::updateOrbit() {
	float z = m_distance*cos(m_rotations.y*M_PI/180.f)*sin(m_rotations.x*M_PI/180.f);
	float x = m_distance*sin(m_rotations.y*M_PI/180.f)*sin(m_rotations.x*M_PI/180.f);
	float y = m_distance*cos(m_rotations.x*M_PI/180.f);

	m_target = m_targetNode->getPosition();

	position = m_target + glm::vec3(x,y,z);
	m_viewDirty = true;
}

}