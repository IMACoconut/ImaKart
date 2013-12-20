#pragma once

#include <glm/glm.hpp>

namespace Phys {
	class BSphere {
	public:
		BSphere(const glm::vec3& pos, float radius = 1.f);
		BSphere(const BSphere& other);
		BSphere& operator= (const BSphere& other);

		void extends(const glm::vec3& point);
		void extends(const BSphere& other);
		bool collide(const BSphere& other);
		bool contains(const glm::vec3& point);
		float radius() const;

	protected:
		glm::vec3 m_pos;
		float m_radius;
	};
}