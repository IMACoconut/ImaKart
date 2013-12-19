#pragma once
#include <glm/glm.hpp>

class AABB3D
{
private:
	glm::vec3 size;
	glm::vec3 pos;

public:
	AABB3D() : 
		AABB3D(glm::vec3(0,0,0), glm::vec3(0,0,0)){}

	AABB3D(const glm::vec3& pos, const glm::vec3& size) : 
		size(size), pos(pos){}

	~AABB3D() = default;

	bool collide(const AABB3D& other){
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

	bool collide(const glm::vec3& point){
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

	void extends(const glm::vec3& point){
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
};