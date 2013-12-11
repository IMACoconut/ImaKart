#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <SFML/System/Vector3.hpp>
#include <Game/Entity.hpp>
#include <Graphics.hpp>

//namespace Game{

enum KartCondition{
	NORMAL,
	FLIP
};

typedef enum {
	KartType_1,
	KartType_2,
	KartType_3
} KartType;


class Item;
class Kart: public Entity
{
public:
	Kart(int id);
	~Kart();
	
		void loadIntoScene(Graph::Scene& s);
		void update(float elapsed);				//mise à jours de tout les paramètre du kart
		void moveForward(bool state);         // fais monter l'accelération à speedMaxForward
		void moveBack(bool state);			//fais monter l'accelération à speedMaxBack
		void deccelerate(float lvl, bool state);//fait revennir l'acceleration à 0
		void turnLeft(bool state);			//fait tourner le vecteur direction sur la gauche
		void turnRight(bool state);			//fait tourner le vecteur direction sur la droite
		void useItem(bool state);				//utilise un objet
	void addAlteration(Alteration* alteration);

	void giveItem(Item* item);

	private:
		Graph::Mesh mesh;
		bool rolls = false;
		bool backtrack = false;
		bool slowDown = false;
		bool right = false;
		bool left = false;
};
//}