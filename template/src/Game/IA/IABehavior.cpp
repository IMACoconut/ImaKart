#include <Game/IA/IABehavior.hpp>
#include <Game/Kart.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

//static const float EPSILON_Angle = 1;

IABehavior::IABehavior(Kart& kart/*, std::vector<Checkpoint*> map_check*/) :
	KartBehavior(kart)//, m_directions(map_check)
{}

void IABehavior::pusshPrioritie(IAPriority prioritie){
	m_priorities.push_back(prioritie);
}

void IABehavior::punishPlayer(){
	/*auto items = m_kart.get<std::vector<Item*>>("items");
	if(items.size())
	{
		item.use(m_kart);
	}*/
}

void IABehavior::findItem(){
	/*auto items = m_kart.get<std::vector<Item*>>("items");
	if(items.size() >= MAX_ITEMS)
		break;
	auto target = GameLogic::getClosestItem(m_kart, 50);
	if(!target)
		break;

	m_directions.push(target.getPosition());*/
}

void IABehavior::goToTheNextCheckpoint(float elapsed){
	//auto pos = m_kart.get<glm::vec3>("position");
	int toCheck = m_kart.get<int>("checkpoint") +1;
	if(toCheck == (int)m_directions.size())
		toCheck = 1;

	glm::vec3 checkPosition = m_directions[toCheck]->getPosition();
	glm::vec3 direction = m_kart.get<glm::vec3>("position") - checkPosition;
	glm::vec2 direction2D = glm::normalize(glm::vec2(direction.x, direction.z));
	glm::vec2 forward2D = glm::normalize(glm::vec2(m_kart.get<glm::vec3>("forward").x, m_kart.get<glm::vec3>("forward").z));
	
	float angle;
	if(forward2D == direction2D)
		angle = 0;
	else
		angle = glm::orientedAngle(forward2D, direction2D);

	float distance = glm::length(direction);
	float currentSpeed = m_kart.get<float>("currentSpeed");
	float acceleration = m_kart.get<float>("acceleration");
	
	if(angle < -0.000001)
		m_kart.turn(1.f, elapsed);
	else if(angle > 0.000001)
		m_kart.turn(-1.f, elapsed);
	else
		m_kart.turn(0, elapsed);

	//float factorAngle = currentSpeed / distance;
 	//std::cout<<angle<<" : "<<distance<<std::endl;

	if(distance < 200){
		if(currentSpeed >= 4){
			if(fabs(angle) < 170)
				m_kart.accelerate(-1.f, elapsed);
			else if(fabs(angle) < 175)
				m_kart.accelerate(0, elapsed);
			else
				m_kart.accelerate(1.f, elapsed);
		}
		else if(currentSpeed >=2){
			if(fabs(angle) < 160)
				m_kart.accelerate(-1.f, elapsed);
			else if (fabs(angle) < 170)
				m_kart.accelerate(0.f, elapsed);
			else
				m_kart.accelerate(1.f, elapsed);
		}
		else
			if(fabs(angle) < 110)
				m_kart.accelerate(-1.f, elapsed);
			else if(fabs(angle) < 155)
				m_kart.accelerate(0, elapsed);
			else
				m_kart.accelerate(1.f, elapsed);
	}
	else if(distance < 500){
		if(currentSpeed >= 4){
			if(fabs(angle) < 160)
				m_kart.accelerate(-1.f, elapsed);
			else if(fabs(angle) < 165)
				m_kart.accelerate(0, elapsed);
			else
				m_kart.accelerate(1.f, elapsed);
		}
		else if(currentSpeed >=2){
			if(fabs(angle) < 155)
				m_kart.accelerate(-1.f, elapsed);
			else if (fabs(angle) < 160)
				m_kart.accelerate(0.f, elapsed);
			else
				m_kart.accelerate(1.f, elapsed);
		}
		else
			if(fabs(angle) < 95)
				m_kart.accelerate(-1.f, elapsed);
			else if(fabs(angle) < 145)
				m_kart.accelerate(0, elapsed);
			else
				m_kart.accelerate(1.f, elapsed);
	}
	else
		m_kart.accelerate(1.f, elapsed);

}

void IABehavior::onUpdate(float elapsed)
{
	/*for(auto i : m_priorities) {
		switch(i) {
			case PUNISH_PLAYER:
				{
					punishPlayer();
				}
				break;

			case FIND_ITEM:
				{
					findItem();
				}
				break;
			case STEP_FORWARD:
				{
					goToTheNextCheckpoint();

				}
				break;
		}
	}*/
		goToTheNextCheckpoint(elapsed);
}