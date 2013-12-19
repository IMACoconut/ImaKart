#pragma once
#include <Utility.hpp>
#include <Game/IA/ItemSpawnBehavior.hpp>
#include <Game/Logic/Checkpoint.hpp>
#include <Game/Kart.hpp>

class Item;
class Map;
class ItemSpawn : public Checkpoint {
public:
	ItemSpawn(Map& m, float delay);
	bool isReached(Kart& kart);
	bool hasItem() const;
	void update(float elapsed);

private:
	ItemSpawnBehavior m_behavior;
	Item* m_item;
};