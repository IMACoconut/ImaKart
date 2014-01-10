#pragma once

#include <Game/IA/KartBehavior.hpp>

class PlayerBehavior : public KartBehavior {
public:
	PlayerBehavior(Kart& kart, int playerId);

protected:
	void onUpdate(float elapsed);
	
	int m_playerId, m_controllerId;
};