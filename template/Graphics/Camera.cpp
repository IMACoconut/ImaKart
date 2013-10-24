#include <Graphics/Camera.hpp>
#include <Graphics/Render.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace Graph {
	Camera::Camera() :
		Node(),
		m_view(), m_proj(),
		m_projDirty(true), m_viewDirty(true),
		m_fov(60),
		m_near(.1f), m_far(1000.f),
		m_width(1), m_height(1),
		m_pos(4,3,3)
	{

	}

	void Camera::setAspect(float width, float height)
	{
		m_width = width;
		m_height = height;
		m_projDirty = true;
	}

	void Camera::draw() {
		if(m_projDirty)
			updateProjectionMatrix();
		if(m_viewDirty)
			updateViewMatrix();

		Render::setMatrix(Render::ProjectionMatrix, m_proj);
		Render::setMatrix(Render::ViewMatrix, m_view);
	}

	void Camera::updateProjectionMatrix()
	{
		//m_proj = glm::perspective(m_fov, m_width/m_height, m_near, m_far);

		m_projDirty = false;
	}

	void Camera::updateViewMatrix() {
		//m_view = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
		m_viewDirty = false;
	}

	void Camera::move(const sf::Vector3f& m) {
		m_pos += m;
		m_viewDirty = true;
	}
}