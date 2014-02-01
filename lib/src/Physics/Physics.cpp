#include <Physics/Physics.hpp>
#include <Graphics/Tools/Node.hpp>
#include <Physics/AABB3D.hpp>
#include <Physics/BSphere.hpp>
#include <Physics/Collidable.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <vector>


namespace Phys {



	Physics::Physics() : 
		myBroadphase(),
		myCollisionConfiguration(),
		myDispatcher(&myCollisionConfiguration),		
		mySequentialImpulseConstraintSolver(),
		myWorld(&myDispatcher, &myBroadphase, &mySequentialImpulseConstraintSolver,&myCollisionConfiguration)
	{
		myWorld.setGravity(btVector3(0.,-10,0.));
		std::cout << "initialisation Physics" << std::endl;
	}


	/*Physics::Physics(const Physics& P){
		vecCollidable = P.vecCollidable;
	}*/

	void Physics::addCollidable(Collidable* n){
		vecCollidable.push_back(n);
	}

	void Physics::Initialisation() {
		
	}

	void Physics::AddBodyToWorld() {
		for(Collidable* c1:vecCollidable) {
			
			myWorld.addRigidBody(c1->body);
			std::cout << "body added to world" << std::endl;
		}
	}

	void Physics::update(float elapsed) {
		myWorld.stepSimulation( elapsed );

		for(Collidable* c1:vecCollidable) {
			
			glm::vec3 test = c1->collidableNode->getBoundingBox().getCenter();
			c1->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix( c1->matrix );
			glm::mat4 M = glm::make_mat4(c1->matrix); // pos2(c1->matrix[12], c1->matrix[13], c1->matrix[14]); 
			glm::vec3 res ;
			//std::cout << test.x << "," << test.y << "," << test.z << std::endl;
			if(c1->statique == true) res = glm::vec3(0.,0.,0.);
			else res = glm::vec3(M*glm::vec4(test, 1.f)); 

			c1->collidableNode->setPosition(res) ;

			test = c1->collidableNode->getBoundingBox().getSize();
			//std::cout << test.x << "," << test.y << "," << test.z << std::endl;
			//test = c1->collidableNode->getPosition() ; 
	
			c1->collidableNode->update(0);
		}
		
	} 

	Collidable* Physics::getCollidable(int index){
		return vecCollidable[index];
	}



}