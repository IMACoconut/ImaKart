#pragma once

#include <IA/Behavior.hpp>

class Kart;
class Item;
class ItemSpawnBehavior : public ia::Behavior {
public:
	ItemSpawnBehavior(float delay);

	void onUpdate(float elapsed);

	void onKartTrigger(Kart& kart);
	bool hasItem() const;

private:
	float m_delay;
	float m_currentTime;
	Item* m_item;	
};