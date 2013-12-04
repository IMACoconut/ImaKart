#include <Game/Map.hpp>
#include <Game/Logic/Checkpoint.hpp>
#include <Game/Logic/ItemSpawn.hpp>

void Map::update(float e) {
	for(auto c: m_checkpoints)
		c->update(e);
	for(auto i: m_itemSpawns)
		i->update(e);

	for(auto k : m_karts) {
		Kart* kart = std::get<0>(k);
		kart->update(e);
		for(auto c: m_checkpoints)
			c->isReached(*kart);
		for(auto i: m_itemSpawns)
			i->isReached(*kart);
	}
}

Kart* Map::addKart(KartType type) {
	Kart* k = new Kart(m_karts.size());
	m_karts.push_back(std::make_tuple(k, Util::Clock(), 3, false));
	switch(type) {
		case KartType_1:
			// Changer maniabilité, vitesse, etc...
			break;
		case KartType_2:
			break;
		case KartType_3:
			break;
		default:
			break;
	}

	return k;
}

std::vector<KartInfo> Map::getResults() {
	return m_karts;
}

void Map::hasFinishedLoop(Kart& k) {
	int id = k.get<int>("id");
 	auto& infos = m_karts[id];
 	int& loops = std::get<2>(infos);
 	if(loops == 0) {
 		bool& finished = std::get<3>(infos);
 		finished = true;
 		auto& clock = std::get<1>(infos);
 		clock.Pause();
 	} else
 		--loops;

}