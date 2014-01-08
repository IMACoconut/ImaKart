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

typedef enum {
	KartMovement_None = 0x0000,
	KartMovement_Forward = 0x0001,
	KartMovement_Backward = 0x0010,
	KartMovement_Left = 0x0100,
	KartMovement_Right = 0x1000
} KartMovement;

class Alteration;
class Item;
class KartBehavior;
class Kart: public Entity
{
public:
	Kart(int id);
	~Kart();
		
	void setBehavior(KartBehavior* m_behavior);
	void loadIntoScene(Graph::Scene& s);
	void update(float elapsed);				//mise à jours de tout les paramètre du kart
	void accelerate(float factor);
	void turn(float factor);
	void useItem(bool state);				//utilise un objet
	void addAlteration(Alteration* alteration);

	void giveItem(Item* item);

	private:
		KartBehavior* m_behavior;
		Graph::Mesh mesh;
		KartMovement m_movement;
		float m_speedfactor, m_rotatefactor;
};
//}