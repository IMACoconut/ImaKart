#include <Physics/Collidable.hpp>
#include <Graphics/Tools/Node.hpp>




namespace Phys {

	Collidable::Collidable(Graph::Node* n, float mass, float acceleration, float speed, bool isCollidable, 
			        		bool gravity, glm::vec3 direction, glm::vec3 normal) :
	mass(mass), acceleration(acceleration), speed(speed), isCollidable(isCollidable), 
	gravity(gravity), direction(direction), normal(normal), collidableNode(n) {}


}