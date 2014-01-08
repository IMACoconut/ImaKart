#include <Game/Logic/GameLogic.hpp>
#include <Game/Logic/Item.hpp>
#include <Game/Map.hpp>
#include <Game/Kart.hpp>

#include <Graphics.hpp>
#include <Utility.hpp>

GameLogic::GameLogic() :
	m_map(nullptr), m_camera(nullptr)
{}

GameLogic::~GameLogic() {
	delete m_map;
}

GameLogic& GameLogic::getInstance() {
	static GameLogic gl;
	return gl;
}

void GameLogic::setCamera(Graph::Camera* cam) {
	m_camera = cam;
}

Item* GameLogic::randomItem() {
	return new Item();
}

Kart* GameLogic::createKart(KartType type) {
	if(!m_map) {
		Util::LogManager::error("Cannot create a kart before the map has been selected");
		return nullptr;
	}
	return /*m_map->addKart(type)*/ nullptr;
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

Util::XboxInput& GameLogic::getXboxInput() {
	if(!m_camera)
		throw -1;
	return m_camera->getWindow().getXbox();
}

Util::MouseInput& GameLogic::getMouseInput() {
	if(!m_camera)
		throw -1;
	return m_camera->getWindow().getMouse();
}