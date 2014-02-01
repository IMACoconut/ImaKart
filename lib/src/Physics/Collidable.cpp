#include <Physics/Collidable.hpp>
#include <Graphics/Tools/Node.hpp>
#include <iostream>





namespace Phys {

	Collidable::Collidable(Graph::Node* n) :
	collidableNode(n), m_shape(nullptr) {}
	

	void Collidable::Init(btCollisionShape* shape) {
		m_shape = shape;
		myTransform.setIdentity();
		glm::vec3 test = collidableNode->getBoundingBox().getCenter();
			myTransform.setOrigin(  btVector3(test.x,test.y,test.z) ); 
			btVector3 localInertia(0,0,0);
			btScalar mass = 0.5f;

			if ( mass )
				m_shape->calculateLocalInertia( mass, localInertia );

			myMotionState = new btDefaultMotionState(myTransform);
			btRigidBody::btRigidBodyConstructionInfo myBoxRigidBodyConstructionInfo( mass, myMotionState, m_shape, localInertia );
			body = new btRigidBody(myBoxRigidBodyConstructionInfo);
			statique = false;
			

	}

	void Collidable::InitMap(btCollisionShape* shape) {
		m_shape = shape;
		myTransform.setIdentity();
		glm::vec3 test = collidableNode->getBoundingBox().getCenter();
			myTransform.setOrigin( btVector3(test.x,test.y,test.z) ); 
			//std::cout << test.x << "," << test.y << "," << test.z << std::endl;
			//glm::vec3 size = collidableNode->getBoundingBox().getSize();
			//std::cout << size.x << "," << size.y << "," << size.z << std::endl;
			btVector3 localInertia(0,0,0);
			btScalar mass = 0.f;

			if ( mass )
				m_shape->calculateLocalInertia( mass, localInertia );

			myMotionState = new btDefaultMotionState(myTransform);
			btRigidBody::btRigidBodyConstructionInfo myBoxRigidBodyConstructionInfo( mass, myMotionState, m_shape, localInertia );
			body = new btRigidBody(myBoxRigidBodyConstructionInfo);
			this->collidableNode->update(0);
			statique = true;

	}
	


}