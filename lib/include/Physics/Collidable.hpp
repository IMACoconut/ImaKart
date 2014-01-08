#pragma once 
#include <glm/glm.hpp>

namespace Graph { class Node; }


namespace Phys {
	
	class Collidable {
	public:
		Collidable(Graph::Node* n, float mass, float acceleration, float speed, bool isCollidable, 
			        bool gravity, glm::vec3 direction, glm::vec3 normal );
		

		float mass, acceleration, speed; 
		bool isCollidable;
		bool gravity;
		glm::vec3 direction;
		glm::vec3 normal;
		Graph::Node* collidableNode;
				

	};
}