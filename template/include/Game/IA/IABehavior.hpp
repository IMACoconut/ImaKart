#pragma once

#include <vector>
#include <stack>

#include <Game/Logic/Checkpoint.hpp>
#include <Game/IA/KartBehavior.hpp>
#include <Game/Kart.hpp>

class IABehavior : public KartBehavior{
public:
	typedef enum {
		PUNISH_PLAYER,
		FIND_ITEM,
		STEP_FORWARD
	} IAPriority;

	IABehavior(Kart& kart);

protected:
	void onUpdate(float elapsed);

private:
	std::vector<IAPriority> m_priorities;
	std::stack<Checkpoint*> m_directions;
};