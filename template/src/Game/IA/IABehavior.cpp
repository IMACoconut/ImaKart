#include <Game/IA/IABehavior.hpp>
#include <Game/Kart.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

//static const float EPSILON_Angle = 1;

IABehavior::IABehavior(Kart& kart, const std::vector<Checkpoint*>& map_check) :
	KartBehavior(kart), m_directions(map_check)
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

void IABehavior::goToTheNextCheckpoint(){
	//auto pos = m_kart.get<glm::vec3>("position");
	int toCheck = m_kart.get<int>("checkpoint") +1;

	if(toCheck >= (int)(m_directions.size()) )
		toCheck = 0;

	glm::vec3 direction = m_kart.get<glm::vec3>("position") - m_directions[toCheck]->getPosition();
	float angle = glm::orientedAngle(glm::normalize(direction), m_kart.get<glm::vec3>("forward"), m_kart.get<glm::vec3>("up"));
	float distance = glm::length(direction);

	//std::cout<<angle<<" : "<<distance<<std::endl;
	
	if(angle < -0.000001)
		m_kart.turn(1.f);
	else if(angle > 0.000001)
		m_kart.turn(-1.f);
	else
		m_kart.turn(0);
	
	/*if(distance > 700){
		if(fabs(angle) < 90)
			m_kart.accelerate(-1.0);

		else if(fabs(angle) < 135)
			m_kart.accelerate(0);
		else
			m_kart.accelerate(1.f);
	}
	else{*/
		/*if(fabs(angle) < 135)
			m_kart.accelerate(-1.0);
		else if(fabs(angle) < 160)
			m_kart.accelerate(0);
		else*/
			m_kart.accelerate(1.0);


	//}
	/*m_kart.turn(-1.f);
	*/
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
		goToTheNextCheckpoint();
}