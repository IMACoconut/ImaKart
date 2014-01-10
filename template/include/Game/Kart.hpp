#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <SFML/System/Vector3.hpp>
#include <Game/Entity.hpp>
#include <Graphics.hpp>
#include <Physics/Collidable.hpp>
//namespace Game{

enum KartCondition{
	NORMAL,
	FLIP
};

typedef enum {
	KartType_1 = 0,
	KartType_2 = 1,
	KartType_3 = 2
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
	Kart(const Kart&) = delete;
	~Kart();

	void setPosition(glm::vec3 position, float horizontalAngle);
	void updateOrientation(Graph::Heightmap& heightmap, float elapsed);
	void setBehavior(KartBehavior* m_behavior);
	void loadIntoScene(Graph::Scene& s);
	void update(Graph::Heightmap& heightmap, float elapsed);//mise à jours de tout les paramètre du kart
	void accelerate(float factor, float elapsed);
	void turn(float factor, float elapsed);
	void useItem(bool state);				//utilise un objet
	void addAlteration(Alteration* alteration);

	void giveItem(Item* item);

	Graph::Mesh* getMesh() { return &mesh;}
	void physxKart(Graph::Heightmap& heightmap, float elapsed);

	Graph::Mesh* getMesh() { return &mesh; };
		Graph::Mesh mesh;

		Phys::Collidable collidable;


	private:
		KartBehavior* m_behavior;
		KartMovement m_movement;
		Graph::Material texture;
		//float m_speedfactor, m_rotatefactor;
};
//}