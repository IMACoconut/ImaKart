#include <Game/IA/KartBehavior.hpp>

KartBehavior::KartBehavior(Kart& kart) :
	m_kart(kart)
{}

void KartBehavior::addCheckpoints(std::vector<Checkpoint*> map_check){
	m_directions = map_check;
}