#include <Game/Logic/GameLogic.hpp>
#include <Game/Logic/Item.hpp>
#include <Game/Map.hpp>
#include <Game/kart.hpp>

GameLogic::GameLogic() :
	m_map(nullptr)
{}

GameLogic::~GameLogic() {
	delete m_map;
}

GameLogic& GameLogic::getInstance() {
	static GameLogic gl;
	return gl;
}

Item* GameLogic::randomItem() {
	return new Item();
}

Kart* GameLogic::createKart(KartType type) {
	if(!m_map) {
		Util::LogManager::error("Cannot create a kart before the map has been selected");
		return nullptr;
	}
	return m_map->addKart(type);
}

void GameLogic::update(float elapsed) {
	m_map->update(elapsed);
}

void GameLogic::loadMap(const std::string& map) {
	m_map = new Map;
}

std::vector<KartInfo> GameLogic::getRaceResults() {
	return m_map->getResults();
}