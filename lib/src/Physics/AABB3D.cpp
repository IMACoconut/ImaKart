#include <Physics/AABB3D.hpp>

namespace Phys {

	AABB3D::AABB3D(const glm::vec3& pos, const glm::vec3& size) : 
		size(size), pos(pos){}

	bool AABB3D::collide(const AABB3D& other){
		if(other.pos.x >= this->pos.x + this->size.x ||
			other.pos.x + other.size.x <= this->pos.x ||
			other.pos.y >= this->pos.y + this->size.y ||
			other.pos.y + other.size.y <= this->pos.y ||
			other.pos.z >= this->pos.z + this->size.z ||
			other.pos.z + other.size.z <= this->pos.z)
			return false;
		else
			return true;
	}

	bool AABB3D::collide(const glm::vec3& point){
		if(point.x >= this->pos.x &&
			point.x < this->pos.x + this->size.x &&
			point.y >= this->pos.y &&
			point.y < this->pos.y + this->size.y &&
			point.z >= this->pos.z &&
			point.z < this->pos.z + this->size.z)
			return true;
		else
			return false;
	}

	void AABB3D::extends(const glm::vec3& point){
		if(!(point.x >= this->pos.x &&
			point.x < this->pos.x + this->size.x))
			this->size.x = point.x - this->pos.x;
		if(!(point.y >= this->pos.y &&
			point.y < this->pos.y + this->size.y))
			this->size.y = point.y - this->pos.y;
		if(!(point.z >= this->pos.z &&
			point.z < this->pos.z + this->size.z))
			this->size.z = point.z - this->pos.z;
	}

	void AABB3D::extends(const AABB3D& other) {
		extends(other.pos);
		extends(other.pos+other.size);
	}

	glm::vec3 AABB3D::getCenter() const {
		glm::vec3 center(pos+size);
		center /= 2;
		return center;
	}

	glm::vec3 AABB3D::getSize() const {
		return size;
	}
}