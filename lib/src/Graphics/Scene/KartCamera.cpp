#include <Graphics/Scene/KartCamera.hpp>
#include <Utility/Input/XboxInput.hpp>
#include <Utility/Input/MouseInput.hpp>
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

namespace Graph {

	KartCamera::KartCamera(Util::Window& window, Node* target) : OrbitCamera(window, target){}

	KartCamera::~KartCamera() {}

	void KartCamera::onUpdate(float elapsed) {
		
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

			rotate(rsaxis.x*elapsed*50, rsaxis.y*elapsed*50);
		}
		auto move = m_window.getMouse().getMouseDelta();
		float wheel = m_window.getMouse().getWheelDelta();
		zoom(wheel*elapsed*5.f);
		rotate(move.x*elapsed, move.y*elapsed);
		updateOrbit();
		
	}

	void KartCamera::updateOrbit() {

		glm::mat4 kartMMatrix = m_targetNode->getModelMatrix();
/*
		float z = m_distance*cos(m_rotations.y*M_PI/180.f)*sin(m_rotations.x*M_PI/180.f);
		float x = m_distance*sin(m_rotations.y*M_PI/180.f)*sin(m_rotations.x*M_PI/180.f);
		float y = m_distance*cos(m_rotations.x*M_PI/180.f);azezaezaezaeza
*/
		if(m_targetNode)
			m_target = m_targetNode->getPosition() + glm::vec3(glm::scale(glm::mat4(), m_targetNode->getScale()) * glm::vec4(0, 50, 0, 1));
		else
			m_target = glm::vec3(0,0,0);
		float lerp = 0.3f;
		//position += (m_target+glm::vec3(0,20,0) - position) * lerp;
		position += (glm::vec3(kartMMatrix * glm::vec4(-2*100, 2*80, 0, 1)) - position) * lerp;//m_target + glm::vec3(kartRotat * glm::vec4(x,y,z,1));
		m_viewDirty = true;
	}

}