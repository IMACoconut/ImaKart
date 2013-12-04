#include <Game/IA/ItemSpawnBehavior.hpp>
#include <Game/Logic/GameLogic.hpp>
#include <Game/Logic/Item.hpp>
#include <Game/kart.hpp>

ItemSpawnBehavior::ItemSpawnBehavior(float delay) :
	m_delay(delay),
	m_currentTime(0),
	m_item(nullptr)
{

}

void ItemSpawnBehavior::onUpdate(float elapsed) {
	if(m_item)
		return;

	m_currentTime += elapsed;
	if(m_currentTime >= m_delay) {
		m_currentTime = 0.f;
		m_item = GameLogic::getInstance().randomItem();
	}
}

bool ItemSpawnBehavior::hasItem() const {
	return (m_item != nullptr);
}

void ItemSpawnBehavior::onKartTrigger(Kart& kart) {
	kart.giveItem(m_item);
	m_item = nullptr;
}