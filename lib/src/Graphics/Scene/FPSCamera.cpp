#include <Graphics/Scene/FPSCamera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Window/Event.hpp>

namespace Graph {
	FPSCamera::FPSCamera(Util::Window& window, const glm::vec3& pos, const glm::vec3& dir, float moveSpeed, float rotateSpeed) :
		Camera(window, pos), m_moveSpeed(moveSpeed), m_rotateSpeed(rotateSpeed)
	{
		lookAt(pos+dir);
	}

	void FPSCamera::onUpdate(float elapsed) {
		glm::vec3 mv(0,0,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			mv += m_forward*elapsed*m_moveSpeed;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			mv -= m_forward*elapsed*m_moveSpeed;
	
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			mv += m_left*elapsed*m_moveSpeed;
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			mv -= m_left*elapsed*m_moveSpeed;

		move(mv); 
	}

	void FPSCamera::move(const glm::vec3& m) {
		position += m;
		m_viewDirty = true;
	}

	void FPSCamera::rotate(float horizontal, float vertical) {
		m_rotations.y -= horizontal*0.005f*5;
		m_rotations.x += vertical*0.005f*5;

		if(m_rotations.x < -89.f)
			m_rotations.x = -89.f;
		else if(m_rotations.x > 89.f)
			m_rotations.x = 89.f;

		glm::mat4 rot;
		rot = glm::rotate(rot, m_rotations.y, absoluteUp());
		rot = glm::rotate(rot, m_rotations.x, absoluteLeft());
		m_forward = glm::vec3(rot*glm::vec4(absoluteForward(), 1.f));
		m_left = -glm::cross(m_forward, absoluteUp());
		m_target = position + m_forward;
		m_viewDirty = true;
	}
}