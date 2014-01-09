#include <Game/Logic/Checkpoint.hpp>
#include <Game/Kart.hpp>
#include <Game/Map.hpp>

int Checkpoint::countCheck = 0;

Checkpoint::Checkpoint(Map& m, int pos) :
	m_map(m), m_pos(pos)
{ ++countCheck;}

bool Checkpoint::isReached(Kart& kart) {
	int kartCheck = kart.get<int>("checkpoint");
	bool reach = glm::length(kart.get<glm::vec3>("position")-position) < DIST_FACTOR;
	if(reach && (m_pos == kartCheck + 1 || kartCheck+1 == countCheck)) {// begin/end checkpoint
		kartCheck = m_pos;
		if(m_pos == 0)	
			m_map.hasFinishedLoop(kart);
	//std::cout<<"reached"<< m_pos << std::endl;
	}
	kart.set<int>("checkpoint", kartCheck);
	return reach;
}