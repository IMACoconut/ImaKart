#include <Core/Transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Core {
	Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& sc, Transform* pa) : 
		position(pos), rotation(rot), scale(sc), 
		forward(1,0,0), up(0,1,0), right(0,0,1), 
		parent(pa)
	{}

	void Transform::move(const glm::vec3& move) 
	{
		position += move;
	}

	void Transform::rotate(float x, float y)
	{
		rotation.x += x;
		rotation.y += y;
	}

	void Transform::lookAt(const glm::vec3& target)
	{
		glm::vec3 dir = glm::normalize(target-position);
		rotation.x += glm::orientedAngle(dir, forward, Right());
		rotation.y += glm::orientedAngle(dir,target,Up());
		forward = dir;
		right = glm::cross(forward, up);
		up = glm::cross(forward, right);
	}

	glm::mat4 Transform::matrix() {
		glm::mat4 id;
		id = glm::scale(id, scale);
		id = glm::rotate(id, rotation.x, Up());
		id = glm::rotate(id, rotation.y, Right());
		id = glm::translate(id, position);
		//m_matrix = id;
		//m_isDirty = false;
		
		id *= parent->matrix();
		
		return id;
	}


	Transform& Transform::operator*=(Transform& other) {
		scale *= other.scale;
		rotation += other.rotation;
		position += other.position;
		return *this;
	}

	glm::vec3 Transform::Up() {
		static glm::vec3 v(0,1,0);
		return v;
	}

	glm::vec3 Transform::Right() {
		static glm::vec3 r(0,0,1);
		return r;
	}

	glm::vec3 Transform::Forward() {
		static glm::vec3 f(1,0,0);
		return f;
	}
}