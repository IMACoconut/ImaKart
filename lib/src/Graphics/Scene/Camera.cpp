#include <Graphics/Scene/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Graph {
	Camera::Camera() :
		Node(),
		m_view(), m_proj(),
		m_projDirty(true), m_viewDirty(true),
		m_fov(60),
		m_near(.1f), m_far(10000.f),
		m_width(1), m_height(1),
		m_forward(absoluteForward()), m_left(absoluteLeft()), m_up(absoluteUp()),
		m_rotations(0,0,0)
	{
		move(glm::vec3(3.1,0,0));
	}

	void Camera::setAspect(float width, float height)
	{
		m_width = width;
		m_height = height;
		m_projDirty = true;
	}

	glm::vec2 Camera::getAspect() const {
		return glm::vec2(m_width, m_height);
	}

	glm::vec2 Camera::getFrustum() const {
		return glm::vec2(m_near, m_far);
	}

	void Camera::draw() {
		if(m_projDirty)
			updateProjectionMatrix();
		if(m_viewDirty)
			updateViewMatrix();

		//Render::setMatrix(Render::ProjectionMatrix, m_proj);
		//Render::setMatrix(Render::ViewMatrix, m_view);
	}

	glm::mat4 Camera::getProjMatrix() const {
		return m_proj;
	}

	glm::mat4 Camera::getViewMatrix() const {
		return m_view;
	}


	void Camera::updateProjectionMatrix()
	{
		m_proj = glm::perspective(m_fov, m_width/m_height, m_near, m_far);

		m_projDirty = false;
	}

	void Camera::updateViewMatrix() {
		m_view = glm::lookAt(position, position+m_forward, m_up);
		m_viewDirty = false;
	}

	void Camera::move(const glm::vec3& m) {
		position += m;
		m_viewDirty = true;
	}

	void Camera::rotate(float horizontal, float vertical) {
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
		m_viewDirty = true;

	}

	glm::vec3 Camera::forward() {
		return m_forward;
	}

	glm::vec3 Camera::backward() {
		return -m_forward;
	}

	glm::vec3 Camera::left() {
		return m_left;
	}

	glm::vec3 Camera::right() {
		return -m_left;
	}

	glm::vec3 Camera::up() {
		return m_up;
	}

	glm::vec3 Camera::down() {
		return -m_up;
	}

	glm::vec3 Camera::absoluteForward() {
		return glm::vec3(-1,0,0);
	}

	glm::vec3 Camera::absoluteLeft() {
		return glm::vec3(0,0,1);
	}

	glm::vec3 Camera::absoluteUp() {
		return glm::vec3(0,1,0);
	}
}