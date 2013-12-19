#include <Game/IA/IABehavior.hpp>
#include <Game/Kart.hpp>

IABehavior::IABehavior(Kart& kart) :
	KartBehavior(kart)
{}

void IABehavior::onUpdate(float elapsed)
{
	for(auto i : m_priorities) {
		switch(i) {
			case PUNISH_PLAYER:
				{
					/*auto items = m_kart.get<std::vector<Item*>>("items");
					if(items.size())
					{
						item.use(m_kart);
					}*/
				}
				break;

			case FIND_ITEM:
				{
					/*auto items = m_kart.get<std::vector<Item*>>("items");
					if(items.size() >= MAX_ITEMS)
						break;
					auto target = GameLogic::getClosestItem(m_kart, 50);
					if(!target)
						break;

					m_directions.push(target.getPosition());*/
				}
				break;
			case STEP_FORWARD:
				{
					//auto pos = m_kart.get<glm::vec3>("position");
					if(m_directions.top()->isReached(m_kart))
						m_directions.pop();

				}
				break;
		}
	}
}