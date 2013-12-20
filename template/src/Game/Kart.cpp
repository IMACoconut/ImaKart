#include <Game/Kart.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <Game/VectorAlt.hpp>
#include <Game/Logic/Item.hpp>
#include <Game/IA/KartBehavior.hpp>

//std::string t = get<std::string>("skin");

	Kart::Kart(int id) :
		m_behavior(nullptr),
		m_speedfactor(0), m_rotatefactor(0)
	{
		add("id", new Component<int>(1, id));
		add("skin", new Component<std::string>(1, ""));
		add("hp", new Component<int>(1, 1));
		add("condition", new Component<KartCondition>(1, NORMAL));
		add("speedMaxForward", new Component<float>(1, 2));
		add("speedMaxBack", new Component<float>(1, 1.25));
		add("currentSpeed", new Component<float>(1, 0));
		add("acceleration", new Component<float>(1, 0.03f));
		add("brake", new Component<float>(1,0.01f));
		add("maniability", new Component<float>(1, .1));
		add("position", new Component<glm::vec3>(1, glm::vec3(0, 0, 0)));
		add("forward", new Component<glm::vec3>(1, glm::vec3(1, 0, 0)));
		add("left", new Component<glm::vec3>(1, glm::vec3(0, 0, 1)));
		add("up", new Component<glm::vec3>(1, glm::vec3(0, 1, 0)));
		add("horizontalAngle", new Component<float>(1, 0));
		add("verticalAngle", new Component<float>(1, 0));
		add("alterations", new Component<VectorAlt>(1, VectorAlt()));
		//add("items", new Component<ItemList>(1, nullptr));
	}

	Kart::~Kart(){

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
		if(m_behavior)
			m_behavior->update(elapsed);

		bool updateRotation = true, updatePosition = true;
		if(m_speedfactor > 0) {
			float currentSpeed = get<float>("currentSpeed");
			currentSpeed += get<float>("acceleration")*elapsed*m_speedfactor;
			if(currentSpeed > get<float>("speedMaxForward"))
				currentSpeed = get<float>("speedMaxForward");
			
			set<float>("currentSpeed", currentSpeed);
		} else if(m_speedfactor < 0){
			float currentSpeed = get<float>("currentSpeed");
			if(currentSpeed > -get<float>("speedMaxBack"))
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

		/*
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
			

		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
						
		}else{
			float currentSpeed = get<float>("currentSpeed");
			
			currentSpeed -= get<float>("brake")*elapsed;
			if(currentSpeed < 0)
				currentSpeed = 0;
			set<float>("currentSpeed", currentSpeed);
		} 



		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
			
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			
		} else {
			updateRotation = false;
		}


		/*switch(get<KartCondition>("conditon")){
			case NORMAL:
			{
				*/
			/*}
			break;
			
			default:
			break;
		}*/
		/*	glm::vec3 dir(0,0,0);
			{
				float cs = get<float>("currentSpeed");
				if(rolls) {
					if(cs< 1)
						cs += .1*elapsed;
					else
						cs = 1;			
				} else {
					if(cs > 0)
						cs -= .05*elapsed;
					else
						cs = 0;
				}
				set<float>("currentSpeed", cs);
			}
			{
				if(left || right) {
					std::cout << "rotate" << std::endl;
					float horizontalAngle = get<float>("horizontalAngle");
					glm::vec3 forward = get<glm::vec3>("forward");
					glm::vec3 leftv = get<glm::vec3>("left");

					if(left)
						horizontalAngle -= get<float>("maniability")*.01f;
					else
						horizontalAngle += get<float>("maniability")*.01f;

					glm::mat4 rot;
					rot = glm::rotate(rot, horizontalAngle, get<glm::vec3>("up"));
					forward = glm::vec3(rot*glm::vec4(forward, 1.f));
					leftv = glm::vec3(rot*glm::vec4(leftv, 1.f));
					set<glm::vec3>("forward", forward);
					set<glm::vec3>("left", leftv);
					mesh.setRotation(glm::vec3(0,horizontalAngle,0));
				}
			}*/
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
		/*if(rolls){
			float currentSpeed = get<float>("currentSpeed");
			if(currentSpeed < get<float>("speedMaxForward"))
				currentSpeed += get<float>("acceleration");
			set<float>("currentSpeed", 1.f);
		}
		if(backtrack){
			float currentSpeed = get<float>("currentSpeed");
			if(currentSpeed < get<float>("speedMaxBack"))
				currentSpeed -= get<float>("acceleration");
			set<float>("currentSpeed", currentSpeed);
		}
		if(slowDown){
			float currentSpeed = get<float>("currentSpeed");
			float acceleration = get<float>("acceleration");
			if(currentSpeed > 0)
				currentSpeed -= acceleration;
			else if(currentSpeed < 0)
				currentSpeed += acceleration;
			set<float>("currentSpeed", currentSpeed);
		}
		if(left){
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
		if(right){
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
		}*/
	}

	void Kart::accelerate(float factor){
		m_speedfactor = factor;
		//std::cout << "accelerate: " << factor << std::endl;
	}

	void Kart::turn(float factor){
		m_rotatefactor = factor;
		//std::cout << "rotate: " << factor << std::endl;
	}

	void Kart::useItem(bool state){}

	void Kart::giveItem(Item* i) {}

//}