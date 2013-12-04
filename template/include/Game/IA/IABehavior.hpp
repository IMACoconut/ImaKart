#pragma once

#include <vector>
#include <stack>

#include <Game/Logic/Checkpoint.hpp>
#include <IA/Behavior.hpp>
#include <Game/kart.hpp>

class IABehavior : public ia::Behavior{
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
	Kart& m_kart;
	std::vector<IAPriority> m_priorities;
	std::stack<Checkpoint*> m_directions;
};