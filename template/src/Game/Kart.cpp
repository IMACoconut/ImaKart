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

	void Kart::updateOrientation(Graph::Heightmap& heightmap){
float factor = 0.01;
float sc = 50.;

		float verticalAngle = get<float>("verticalAngle");
		float lateralAngle = get<float>("lateralAngle");
		glm::vec3 position = get<glm::vec3>("position");
		glm::vec3 forward = position + factor * get<glm::vec3>("forward");
		glm::vec3 left = position + factor * get<glm::vec3>("left");

		//glm::vec3 newForward = glm::vec3(forward.x, sc * heightmap.offsetHeight(forward.x/sc, forward.z/sc), forward.z);
		//glm::vec3 newleft = glm::vec3(left.x, sc * heightmap.offsetHeight(left.x/sc, left.z/sc), left.z);
		glm::vec3 newForward = glm::vec3(glm::normalize(glm::vec2(forward.x, forward.z)), sc * heightmap.offsetHeight(forward.x/sc, forward.z/sc));
		glm::vec3 newleft = glm::vec3(glm::normalize(glm::vec2(left.x, left.z)), sc * heightmap.offsetHeight(left.x/sc, left.z/sc));
		newForward=glm::vec3(newForward.x, newForward.z, newForward.y);
		newleft=glm::vec3(newleft.x, newleft.z, newleft.y);


std::cerr<<forward.y<<" "<<newForward.y<<std::endl;
		set<float>("verticalAngle", verticalAngle +  glm::orientedAngle(glm::normalize(forward), glm::normalize(newForward), left));
		set<float>("lateralAngle", lateralAngle +  glm::orientedAngle(glm::normalize(left), glm::normalize(newleft), forward));
	}

	void Kart::loadIntoScene(Graph::Scene& s){
		this->mesh.loadFromFile("../resources/models/kart.3DS");
		s.addMesh(&mesh);
		mesh.setRotation(glm::vec3(-90,0,0));
	}

	void Kart::setBehavior(KartBehavior* behavior) {
		m_behavior = behavior;
	}

	void Kart::update(float elapsed){

		VectorAlt alterations = get<VectorAlt>("alterations"); 
		if(!alterations.isEmpty()){
		alterations.apply(*this);
 		}
 		set<VectorAlt>("alterations", alterations);


		if(m_behavior)
			m_behavior->update(elapsed);



		//bool updateRotation = true, updatePosition = true;
		/*if(m_speedfactor > 0) {
			float currentSpeed = get<float>("currentSpeed");
			currentSpeed += get<float>("acceleration")*elapsed*m_speedfactor;
			if(currentSpeed > get<float>("speedMaxForward"))
				currentSpeed = get<float>("speedMaxForward");
			
			set<float>("currentSpeed", currentSpeed);
		} else if(m_speedfactor < 0){
			float currentSpeed = get<float>("currentSpeed");
			if(currentSpeed < -get<float>("speedMaxBack"))
				currentSpeed -= get<float>("acceleration")*elapsed*m_speedfactor;
			set<float>("currentSpeed", currentSpeed);
		} else 
			updatePosition = false;

		if(m_rotatefactor > 0) {
			float horizontalAngle = get<float>("horizontalAngle");
			horizontalAngle -= get<float>("maniability")*elapsed*m_rotatefactor;
			set<float>("horizontalAngle", horizontalAngle);
		} else if(m_rotatefactor < 0) {
			float horizontalAngle = get<float>("horizontalAngle");
			horizontalAngle += get<float>("maniability")*elapsed*m_rotatefactor;
			set<float>("horizontalAngle", horizontalAngle);
		} else {
			updateRotation = false;
		}

			if(updateRotation) {
				//std::cout << get<float>("horizontalAngle") << std::endl;
				glm::vec3 forward = get<glm::vec3>("forward");
				glm::vec3 left = get<glm::vec3>("left");

				glm::mat4 rot;
				rot = glm::rotate(rot, get<float>("horizontalAngle"), get<glm::vec3>("up"));
				forward = glm::vec3(rot*glm::vec4(glm::vec3(1, 0, 0), 1.f));
				left = glm::vec3(rot*glm::vec4(glm::vec3(0, 0, 1), 1.f));
				set<glm::vec3>("forward", forward);
				set<glm::vec3>("left", left);
				mesh.setRotation(glm::vec3(0,get<float>("horizontalAngle"),0));
			}

			if(updatePosition) {
				glm::vec3 dir = get<glm::vec3>("forward")*get<float>("currentSpeed")*elapsed;
				glm::vec3 tmp = dir + get<glm::vec3>("position");
				//std::cout << dir.x << " " << dir.y << " " << dir.z << std::endl;
				set<glm::vec3>("position", tmp);
				mesh.setPosition(tmp);
			}
		*/

		//mise à jour de la position dui kart
		glm::vec3 dir = get<glm::vec3>("forward")*get<float>("currentSpeed")*elapsed;
		glm::vec3 tmp = dir + get<glm::vec3>("position");
		set<glm::vec3>("position", tmp);
		mesh.setPosition(tmp);

		//mise à jour de l'orientation du kart
		glm::vec3 up = get<glm::vec3>("up");
		glm::vec3 forward = get<glm::vec3>("forward");
		glm::vec3 left = get<glm::vec3>("left");

		glm::mat4 rot;
		rot = elapsed*glm::rotate(rot, get<float>("horizontalAngle"), up);
		forward = glm::vec3(rot*glm::vec4(glm::vec3(1, 0, 0), 1.f));
		left = glm::vec3(rot*glm::vec4(glm::vec3(0, 0, 1), 1.f));
		set<glm::vec3>("forward", forward);
		set<glm::vec3>("left", left);
		mesh.setRotation(glm::vec3(0, get<float>("horizontalAngle"), 0));
	}

	void Kart::accelerate(float factor){
	//	m_speedfactor = factor;
		//std::cout << "accelerate: " << factor << std::endl;

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
	//	m_rotatefactor = factor;
		//std::cout << "rotate: " << factor << std::endl;

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