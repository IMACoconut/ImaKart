#include <Game/Logic/ItemSpawn.hpp>
#include <Game/kart.hpp>
#include <Game/Map.hpp>

ItemSpawn::ItemSpawn(Map& m, float delay) :
	Checkpoint(m, -1),
	m_behavior(ItemSpawnBehavior(delay))
{
}

bool ItemSpawn::isReached(Kart& kart) {
	if(!Checkpoint::isReached(kart))
		return false;

	m_behavior.onKartTrigger(kart);
	return true;
}

bool ItemSpawn::hasItem() const {
	return m_behavior.hasItem();
}

void ItemSpawn::update(float elapsed)
{
	m_behavior.onUpdate(elapsed);
}