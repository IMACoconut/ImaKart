#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <SFML/System/Vector3.hpp>
#include <Game/Entity.hpp>

namespace Game{

	class Alteration;

	enum KartCondition{
		NORMAL,
		FLIP
	};

	class Kart:public Entity
	{
	public:
		Kart();
		~Kart();
		
		void update();				//mise à jours de tout les paramètre du kart
		void moveForward();         // fais monter l'accelération à speedMaxForward
		void moveBack();			//fais monter l'accelération à speedMaxBack
		void deccelerate(float lvl);//fait revennir l'acceleration à 0
		void turnLeft();			//fait tourner le vecteur direction sur la gauche
		void turnRight();			//fait tourner le vecteur direction sur la droite
		void useItem();				//utilise un objet
		void addAlteration(Alteration* alteration);
	};
}