#pragma once
#include <glm/glm.hpp>

namespace Phys {
class AABB3D
{
private:
	glm::vec3 size;
	glm::vec3 pos;

public:

	AABB3D(const glm::vec3& pos = glm::vec3(0,0,0), const glm::vec3& size = glm::vec3(0,0,0));

	~AABB3D() = default;

	bool collide(const AABB3D& other);

	bool collide(const glm::vec3& point);

	void extends(const glm::vec3& point);

	void extends(const AABB3D& aabb);

	glm::vec3 getCenter() const;

	glm::vec3 getSize() const;
};
}