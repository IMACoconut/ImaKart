#pragma once

#include <IA/Behavior.hpp>
#include <vector>
#include <Game/Logic/Checkpoint.hpp>

class Kart;
class KartBehavior : public ia::Behavior {
public:
	KartBehavior(Kart& kart);
	virtual ~KartBehavior() {}

protected:
	Kart& m_kart;
};