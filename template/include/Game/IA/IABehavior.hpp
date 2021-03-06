#pragma once

#include <vector>
#include <stack>

#include <Game/IA/KartBehavior.hpp>
#include <Game/Kart.hpp>

class IABehavior : public KartBehavior{
public:
	typedef enum {
		PUNISH_PLAYER,
		FIND_ITEM,
		STEP_FORWARD
	} IAPriority;

	IABehavior(Kart& kart, const std::vector<Checkpoint*>& map_check);


protected:
	void onUpdate(float elapsed);

private:
	std::vector<IAPriority> m_priorities;

	const std::vector<Checkpoint*>& m_directions;


	void pusshPrioritie(IAPriority prioritie);
	void punishPlayer();
	void findItem();
	void goToTheNextCheckpoint(float elapsed);
};