#include <Game/Logic/Checkpoint.hpp>
#include <Game/kart.hpp>
#include <Game/Map.hpp>

Checkpoint::Checkpoint(Map& m, int pos) :
	m_map(m), m_pos(pos)
{}

bool Checkpoint::isReached(Kart& kart) {
	bool reach = glm::length(kart.get<glm::vec3>("position")-position) < DIST_FACTOR;
	if(reach && m_pos == 0) {// begin/end checkpoint
		m_map.hasFinishedLoop(kart);
	}
	return reach;
}