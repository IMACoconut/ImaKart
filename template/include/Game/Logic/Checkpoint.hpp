#pragma once

#include <Graphics/Tools/Node.hpp>

#define DIST_FACTOR 10.f

class Map;
class Kart;
class Checkpoint : public Graph::Node{
public:
	Checkpoint(Map& m, int pos);
	virtual bool isReached(Kart& kart);
protected:
	Map& m_map;
	int m_pos;
private:

};