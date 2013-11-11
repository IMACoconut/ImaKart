#include <Game/kart.hpp>
#include <SFML/System/Vector3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

//std::string t = get<std::string>("skin");

namespace Game{

	Kart::Kart() {
		add("skin", new Component<std::string>(1, ""));
		add("hp", new Component<int>(1, 0));
		add("condition", new Component<KartCondition>(1, NORMAL));
		add("speedMaxForward", new Component<float>(1, 0));
		add("speedMaxBack", new Component<float>(1, 0));
		add("currentSpeed", new Component<float>(1, 0));
		add("acceleration", new Component<float>(1, 0));
		add("maniability", new Component<float>(1, 0));
		add("weight", new Component<float>(1, 0));
		add("position", new Component<glm::vec3>(1, glm::vec3(0, 0, 0)));
		add("forward", new Component<glm::vec3>(1, glm::vec3(1, 0, 0)));
		add("left", new Component<glm::vec3>(1, glm::vec3(0, 1, 0)));
		add("up", new Component<glm::vec3>(1, glm::vec3(0, 0, 1)));
		add("horizontalAngle", new Component<float>(1, 0));
		add("verticalAngle", new Component<float>(1, 0));
		//add("alterations", new Component<AlterationList>(1, nullptr));
		//add("items", new Component<ItemList>(1, nullptr));
	}

	Kart::~Kart(){

	}

	void Kart::update(){
		// while(*alterations != NULL){
		// 	alterations->apply(this);
		// 	*alterations = alterations->next;
		// }

		switch(get<KartCondition>("conditon")){
			case NORMAL:
				set<glm::vec3>("position", get<glm::vec3>("position") + get<float>("currentSpeed") * get<glm::vec3>("forward"));
			break;
			
			default:
			break;
		}
	}

	void Kart::moveForward(){
		float currentSpeed = get<float>("currentSpeed");
		if(currentSpeed < get<float>("speedMaxForward"))
			currentSpeed += get<float>("acceleration");
		set<float>("currentSpeed", currentSpeed);
	}

	void Kart::moveBack(){
		float currentSpeed = get<float>("currentSpeed");
		if(currentSpeed < get<float>("speedMaxBack"))
			currentSpeed -= get<float>("acceleration");
		set<float>("currentSpeed", currentSpeed);
	}

	void Kart::deccelerate(float lvl){
		float currentSpeed = get<float>("currentSpeed");
		float acceleration = get<float>("acceleration");
		if(currentSpeed > 0)
			currentSpeed -= lvl * acceleration;
		else if(currentSpeed < 0)
			currentSpeed +=  lvl * acceleration;
		set<float>("currentSpeed", currentSpeed);
	}

	void Kart::turnLeft(){
		float horizontalAngle = get<float>("horizontalAngle");
		glm::vec3 forward = get<glm::vec3>("forward");
		glm::vec3 left = get<glm::vec3>("left");

		horizontalAngle -= get<float>("maniability")*0.01f;

		glm::mat4 rot;
		rot = glm::rotate(rot, horizontalAngle, get<glm::vec3>("up"));
		forward = glm::vec3(rot*glm::vec4(forward, 1.f));
		left = glm::vec3(rot*glm::vec4(left, 1.f));
		set<glm::vec3>("forward", forward);
		set<glm::vec3>("left", left);
	}

	void Kart::turnRight(){
		float horizontalAngle = get<float>("horizontalAngle");
		glm::vec3 forward = get<glm::vec3>("forward");
		glm::vec3 left = get<glm::vec3>("left");

		horizontalAngle += get<float>("maniability")*0.01f;

		glm::mat4 rot;
		rot = glm::rotate(rot, horizontalAngle, get<glm::vec3>("up"));
		forward = glm::vec3(rot*glm::vec4(forward, 1.f));
		left = glm::vec3(rot*glm::vec4(left, 1.f));
		set<glm::vec3>("forward", forward);
		set<glm::vec3>("left", left);
	}

	void Kart::useItem(){}
}