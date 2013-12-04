#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <SFML/System/Vector3.hpp>
#include <Game/Entity.hpp>

class Alteration;

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
	
	void update(float elapsed);	//mise à jours de tout les paramètre du kart
	void moveForward();         // fais monter l'accelération à speedMaxForward
	void moveBack();			//fais monter l'accelération à speedMaxBack
	void deccelerate(float lvl);//fait revennir l'acceleration à 0
	void turnLeft();			//fait tourner le vecteur direction sur la gauche
	void turnRight();			//fait tourner le vecteur direction sur la droite
	void useItem();				//utilise un objet
	void BonusSpeed(float modif);
	void addAlteration(Alteration* alteration);

	void giveItem(Item* item);
};