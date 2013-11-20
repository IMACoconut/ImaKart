#pragma once

#include <string>
#include <glm/glm.hpp>
#include <SFML/System/Vector3.hpp>
#include <Game/Entity.hpp>
#include <Graphics.hpp>

//namespace Game{

	enum KartCondition{
		NORMAL,
		FLIP
	};

	class Kart:public Entity
	{
	public:
		Kart();
		~Kart();
		
		void loadIntoScene(Graph::Scene& s);
		void update(float elapsed);				//mise à jours de tout les paramètre du kart
		void moveForward(bool state);         // fais monter l'accelération à speedMaxForward
		void moveBack(bool state);			//fais monter l'accelération à speedMaxBack
		void deccelerate(float lvl, bool state);//fait revennir l'acceleration à 0
		void turnLeft(bool state);			//fait tourner le vecteur direction sur la gauche
		void turnRight(bool state);			//fait tourner le vecteur direction sur la droite
		void useItem(bool state);				//utilise un objet

		/*std::string skin;
		int hp;
		KartCondition condition;
		float speedMaxForward;
		float speedMaxBack;
		float currentSpeed;  //[0, speedMax]
		float acceleration;
		float maniability;
		float weight;
		glm::vec3 m_position;
		glm::vec3 m_forward;
		glm::vec3 m_left;
		glm::vec3 m_up;
		float m_horizontalAngle, m_verticalAngle;*/
		//AlterationList alterations;
		//ItemList items;

	private:
		Graph::Mesh mesh;
		bool rolls = false;
		bool backtrack = false;
		bool slowDown = false;
		bool right = false;
		bool left = false;
	};
//}