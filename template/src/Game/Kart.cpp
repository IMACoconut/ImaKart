#include <Game/Kart.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#include <cmath>
#include <Game/VectorAlt.hpp>
#include <Game/Logic/Item.hpp>
#include <Game/IA/KartBehavior.hpp>

//std::string t = get<std::string>("skin");


static const float EPSILON_KART = 0.005;

	Kart::Kart(int id) :
		m_behavior(nullptr)/*,
		m_speedfactor(0), m_rotatefactor(0)*/
	{
		add("id", new Component<int>(1, id));
		add("skin", new Component<std::string>(1, ""));
		add("hp", new Component<int>(1, 1));
		add("condition", new Component<KartCondition>(1, NORMAL));
		add("weight", new Component<float>(1, 5.f));
		add("speedMaxForward", new Component<float>(1, 5.f));
		add("speedMaxBack", new Component<float>(1, -1.f));
		add("currentSpeed", new Component<float>(1, 0.f));
		add("acceleration", new Component<float>(1, 0.01f));
		add("maniability", new Component<float>(1, 0.5f));
		add("position", new Component<glm::vec3>(1, glm::vec3(3, 3, 3)));
		add("forward", new Component<glm::vec3>(1, glm::vec3(1, 0, 0)));
		add("up", new Component<glm::vec3>(1, glm::vec3(0, 1, 0)));
		add("horizontalAngle", new Component<float>(1, 0));
		add("alterations", new Component<VectorAlt>(1, VectorAlt()));
		add("rotat", new Component<glm::mat4>(1, glm::mat4(1.)));
		add("checkpoint", new Component<int>(1, 0));
	}

	Kart::~Kart(){

	}

	void Kart::setPosition(glm::vec3 position, float horizontalAngle){
		set<glm::vec3>("position", position);
		set<float>("horizontalAngle", horizontalAngle);

	}

	void Kart::physxKart(Graph::Heightmap& heightmap, float elapsed){
		glm::vec3 position = get<glm::vec3>("position");
		float mapY = heightmap.realHeight(position.x, position.z);

		if(position.y > mapY)
			position.y -=  elapsed;
		else
			position.y = mapY;

		set<glm::vec3>("position", position);

		mesh.setPosition(position);
	}

	void Kart::updateOrientation(Graph::Heightmap& heightmap, float elapsed){

		float horizontalAngle =get<float>("horizontalAngle"), maniability = get<float>("maniability");
		glm::vec3 position = get<glm::vec3>("position");
		glm::vec3 forward = get<glm::vec3>("forward");
		glm::vec3 up = get<glm::vec3>("up");
		glm::mat4 rotat = get<glm::mat4>("rotat");


		//calcule de l'orientation du kart par rapport au sol
		/*glm::vec3 normalMap = glm::normalize(heightmap.realNormal(position.x, position.z));
		glm::vec3 normalU = glm::cross(normalMap, up);		
		if((normalU.x > EPSILON_KART || normalU.x < -EPSILON_KART) || (normalU.y > EPSILON_KART || normalU.y < -EPSILON_KART) || (normalU.z > EPSILON_KART || normalU.z < -EPSILON_KART)){
			normalU = glm::normalize(normalU);
			float angleNormal = glm::orientedAngle(up, normalMap, normalU);
			
			rotat = glm::rotate(rotat, angleNormal, normalU);
			mesh.setRotationAxe(angleNormal, normalU);
		}

		forward = glm::vec3(rotat*glm::vec4(glm::vec3(1, 0, 0), 1.f));
		up = glm::vec3(rotat*glm::vec4(glm::vec3(0, 1, 0), 1.f));
*/

		//calcule de l'angle horizontale du kart (action du joueur)
		glm::mat4 rotH = elapsed*maniability*glm::rotate(glm::mat4(), horizontalAngle, up);
		forward = glm::vec3(rotH*glm::vec4(glm::vec3(1,0,0), 1.f));
		//forward = glm::vec3(rotH*glm::vec4(forward, 1.f));

		set<glm::vec3>("forward", glm::normalize(forward));
		set<glm::vec3>("up", glm::normalize(up));

		set<float>("horizontalAngle", horizontalAngle);
		set<glm::mat4>("rotat", rotat);


		mesh.setRotation(glm::vec3(0, horizontalAngle, 0));
	}

	void Kart::loadIntoScene(Graph::Scene& s){

this->mesh = Graph::Mesh::CreateAxis();
this->mesh.setScale(glm::vec3(10,10,10));
		//this->mesh.loadFromFile("../resources/models/kart.3DS");
		s.addMesh(&mesh);
	}

	void Kart::setBehavior(KartBehavior* behavior) {
		m_behavior = behavior;
	}

	void Kart::update(Graph::Heightmap& heightmap, float elapsed){

		VectorAlt alterations = get<VectorAlt>("alterations"); 
		if(!alterations.isEmpty()){
			alterations.apply(*this);
 		}
 		set<VectorAlt>("alterations", alterations);


		if(m_behavior)
			m_behavior->update(elapsed);

		//mise à jour de la position dui kart
		glm::vec3 dir = get<glm::vec3>("forward")*get<float>("currentSpeed")*elapsed;
		glm::vec3 tmp = dir + get<glm::vec3>("position");
		set<glm::vec3>("position", tmp);
		mesh.setPosition(tmp);

		//physx
		physxKart(heightmap, elapsed);

		//mise à jour de l'orientation du kart
		updateOrientation(heightmap, elapsed);
	}

	void Kart::accelerate(float factor){

		float currentSpeed = get<float>("currentSpeed");
		float acceleration = get<float>("acceleration");

		if(currentSpeed > 0 - acceleration && currentSpeed < 0 + acceleration && !factor){
			currentSpeed = 0; 
		}
		else if(currentSpeed >= 0){
			currentSpeed += factor * 2 * acceleration - acceleration;
			float speedMaxForward =get<float>("speedMaxForward");
			if(currentSpeed > speedMaxForward)
				currentSpeed = speedMaxForward;
		}
		else if(currentSpeed < 0){
			currentSpeed += factor * 2 * acceleration + acceleration;
			float speedMaxBack =get<float>("speedMaxBack");
			if(currentSpeed < speedMaxBack)
				currentSpeed = speedMaxBack;
		}


		set<float>("currentSpeed", currentSpeed);
	}

	void Kart::turn(float factor){

		if(factor) {
			float horizontalAngle = get<float>("horizontalAngle");
			horizontalAngle -= get<float>("maniability")*factor;
			set<float>("horizontalAngle", horizontalAngle);
		} 
	}

	void Kart::addAlteration(Alteration* alteration){
		VectorAlt alterations = get<VectorAlt>("alterations");
		alterations.pushAlteration(alteration);
		set<VectorAlt>("alterations", alterations);
	}

	void Kart::useItem(bool state){}

	void Kart::giveItem(Item* i) {}

//}