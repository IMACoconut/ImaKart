#include <Physics/BSphere.hpp>

namespace Phys {

	BSphere::BSphere(const glm::vec3& pos, float radius) :
		m_pos(pos), m_radius(radius)
	{

	}
	
	BSphere::BSphere(const BSphere& other) 
	{
		m_pos = other.m_pos;
		m_radius = other.m_radius;
	}

	BSphere& BSphere::operator= (const BSphere& other) {
		m_pos = other.m_pos;
		m_radius = other.m_radius;
		return *this;
	}

	void BSphere::extends(const glm::vec3& point) {
		float dist = glm::length(point - m_pos);
		if(dist > m_radius)
			m_radius = dist;
	}

	void BSphere::extends(const BSphere& other) {
		float len = glm::length(m_pos-other.m_pos)+other.m_radius;
		if(len > m_radius)
			m_radius = len;
	}

	bool BSphere::collide(const BSphere& other) const {
		return glm::length(m_pos-other.m_pos) < (m_radius+other.m_radius);
	}

	bool BSphere::contains(const glm::vec3& point) {
		float dist = glm::length(point - m_pos);
		return dist < m_radius;
	}

	float BSphere::radius() const {
		return m_radius;
	}

	glm::vec3 BSphere::getCenter() const {
		return m_pos;
	}

}