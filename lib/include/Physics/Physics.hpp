#pragma once 
#include <vector>

namespace Phys {
class Collidable;

	class Physics {
	public:
		Physics();
		Physics(std::vector<Collidable*> vec);
		Physics(const Physics& P);
		~Physics();
		void addCollidable(Collidable* n);
		void Update(float elapsed);
		void addForce(Collidable* c);
 		Collidable* getCollidable(int index);
		
	protected:
		std::vector<Collidable*> vecCollidable;
	};
}