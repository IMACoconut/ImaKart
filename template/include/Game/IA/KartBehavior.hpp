#pragma once

#include <IA/Behavior.hpp>
#include <vector>
#include <Game/Logic/Checkpoint.hpp>

class Kart;
class KartBehavior : public ia::Behavior {
public:
	KartBehavior(Kart& kart);
	void addCheckpoints(std::vector<Checkpoint*> map_check);
	std::vector<Checkpoint*> m_directions;
protected:
	Kart& m_kart;
};