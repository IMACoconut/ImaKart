#include <Game/Kart.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#include <cmath>
#include <Game/VectorAlt.hpp>
#include <Game/Logic/Item.hpp>
#include <Game/IA/KartBehavior.hpp>

//std::string t = get<std::string>("skin");



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
		add("brake", new Component<float>(1,0.01f));
		add("maniability", new Component<float>(1, 1.f));
		add("position", new Component<glm::vec3>(1, glm::vec3(3, 3, 3)));
		add("forward", new Component<glm::vec3>(1, glm::vec3(1, 0, 0)));
		add("left", new Component<glm::vec3>(1, glm::vec3(0, 0, 1)));
		add("up", new Component<glm::vec3>(1, glm::vec3(0, 1, 0)));
		add("horizontalAngle", new Component<float>(1, 0));
		add("verticalAngle", new Component<float>(1, 0));
		add("lateralAngle", new Component<float>(1, 0));
		add("alterations", new Component<VectorAlt>(1, VectorAlt()));
		//add("items", new Component<ItemList>(1, nullptr));
		
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
float factor = 1.0;

		float verticalAngle = get<float>("verticalAngle");
		float lateralAngle = get<float>("lateralAngle");
		glm::vec3 position = get<glm::vec3>("position");
		glm::vec3 forward = position + factor * get<glm::vec3>("forward");
		glm::vec3 left = position + factor * get<glm::vec3>("left");

		glm::vec2 tmpForward = glm::normalize(glm::vec2(forward.x, forward.z));
		glm::vec2 tmpLeft = glm::normalize(glm::vec2(left.x, left.z));

		glm::vec3 newForward = glm::vec3(tmpForward.x, tmpForward.y, heightmap.realHeight(tmpForward.x, tmpForward.y));
		glm::vec3 newleft = glm::vec3(tmpLeft.x, tmpLeft.y, heightmap.realHeight(tmpLeft.x, tmpLeft.y));
		newForward=glm::normalize(glm::vec3(newForward.x, newForward.z, newForward.y));
		newleft=glm::normalize(glm::vec3(newleft.x, newleft.z, newleft.y));


std::cerr<<"forwardy :"<<forward.y <<" "<<heightmap.realHeight(position.x, position.z)<<std::endl;
		
		verticalAngle =  glm::orientedAngle(glm::normalize(forward), newForward, left);
		lateralAngle =  glm::orientedAngle(glm::normalize(left), newleft, forward);

		set<float>("verticalAngle", verticalAngle);
		set<float>("lateralAngle", lateralAngle);


		glm::vec3 up = get<glm::vec3>("up");

		glm::mat4 rotF= elapsed*glm::rotate(glm::mat4(), get<float>("horizontalAngle"), up) * glm::rotate(glm::mat4(), get<float>("verticalAngle"), left);
		glm::mat4 rotU= glm::rotate(glm::mat4(), get<float>("verticalAngle"), left) * glm::rotate(glm::mat4(), get<float>("lateralAngle"), forward);
		glm::mat4 rotL = elapsed*glm::rotate(glm::mat4(), get<float>("horizontalAngle"), up) * glm::rotate(glm::mat4(), get<float>("lateralAngle"), forward);
		forward = glm::vec3(rotF*glm::vec4(glm::vec3(1, 0, 0), 1.f));
		up = glm::vec3(rotU*glm::vec4(glm::vec3(0, 1, 0), 1.f));
		left = glm::vec3(rotL*glm::vec4(glm::vec3(0, 0, 1), 1.f));
		set<glm::vec3>("forward", forward);
		set<glm::vec3>("up", up);
		set<glm::vec3>("left", left);


		mesh.setRotation(glm::vec3(lateralAngle, get<float>("horizontalAngle"), verticalAngle));

	}

	void Kart::loadIntoScene(Graph::Scene& s){
		this->mesh.loadFromFile("../resources/models/kart.3DS");
		s.addMesh(&mesh);
		mesh.setRotation(glm::vec3(-90,0,0));
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