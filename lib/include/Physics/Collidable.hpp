#pragma once 
#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>


namespace Graph { class Node; }


namespace Phys {
	
	class Collidable {
	public:
		Collidable(Graph::Node* n);
		void Init(btCollisionShape* shape);
		void InitMap(btCollisionShape* shape);
		~Collidable() {
			delete m_shape;
		}
		

		Graph::Node* collidableNode;
		btCollisionShape* m_shape;
		btTransform myTransform;
		btRigidBody *body;
		btScalar matrix[16];
		btDefaultMotionState *myMotionState;
		bool statique;
				

	};
}