#include <Physics/Physics.hpp>
#include <Graphics/Tools/Node.hpp>
#include <Physics/AABB3D.hpp>
#include <Physics/BSphere.hpp>
#include <Physics/Collidable.hpp>
#include <glm/glm.hpp>

#include <vector>


namespace Phys {

	Physics::Physics(std::vector<Collidable*> vec){
		vecCollidable = vec;
	}

	Physics::Physics(const Physics& P){
		vecCollidable = P.vecCollidable;
	}

	void Physics::addCollidable(Collidable* n){
		vecCollidable.push_back(n);
	}

	void Physics::addForce(Collidable* c) {
		/* add force on a moving object in the scene */ 
	}

	void Physics::Update(float elapsed) {
		for(Collidable* c1:vecCollidable) {
			for(Collidable* c2:vecCollidable) {
				if(c1 == c2) continue ;
					if(c1->isCollidable && c1->isCollidable &&
						(c1->collidableNode->getBoundingBox()).collide(c2->collidableNode->getBoundingBox()) &&
						(c1->collidableNode->getBoundingSphere()).collide(c2->collidableNode->getBoundingSphere())  ) {
						//c1 and c2 are colliding
						
						if(!c1->gravity && !c2->gravity) continue ; //objects not moving
						if(c1->gravity && !c2->gravity) { 
							

						}	





					}
			}
		}
	}

	Collidable* Physics::getCollidable(int index){
		return vecCollidable[index];
	}



}