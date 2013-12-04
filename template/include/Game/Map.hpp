#pragma once

#include <tuple>
#include <Utility.hpp>
#include <Game/kart.hpp>

class Checkpoint;
class ItemSpawn;
typedef std::tuple<Kart*, Util::Clock, int, bool> KartInfo;
// Pointer to kart, clock timer for total time, loops remaining, has finished boolean

class Map {
	public:
		void update(float elapsed);
		Kart* addKart(KartType type);
		std::vector<KartInfo> getResults();
		void hasFinishedLoop(Kart& k);

	private:
		std::vector<KartInfo> m_karts;
		std::vector<Checkpoint*> m_checkpoints;
		std::vector<ItemSpawn*> m_itemSpawns;
};