#include <Game/Logic/GameLogic.hpp>
#include <Game/Logic/Item.hpp>
#include <Game/Map.hpp>
#include <Game/Kart.hpp>

#include <Graphics.hpp>
#include <Utility.hpp>

#include <dirent.h>

GameLogic::GameLogic() :
	m_camera(nullptr)
{
	std::string dirname = "../resources/maps/";
	DIR* dir = opendir(dirname.c_str());
	struct dirent *entry = readdir(dir);
	while(entry != NULL) {
		if (entry->d_type == DT_DIR) {
			std::string dirtmp(entry->d_name);
			if(dirtmp == "." || dirtmp == "..")
			{

			} else {
				std::string tmpfile = dirname+dirtmp+"/map.xml";
            	if(std::ifstream(tmpfile))
            	{
            		MapInfo m(tmpfile);

            		tinyxml2::XMLDocument doc;
            		doc.LoadFile(tmpfile.c_str());
					tinyxml2::XMLElement* root = doc.FirstChildElement("map");
					if(root)
					{
						tinyxml2::XMLElement* info = root->FirstChildElement("info");
						if(info) {
            				m.image = Util::getStringFromXML(info, "preview");
		            		m.name = Util::getStringFromXML(info, "name");
		            		m_maps.push_back(m);
            			}
            		}
            	}
        	}
		}

        entry = readdir(dir);
	}
	closedir(dir);


	KartInfo k("../resources/images/uvtest.png");
	k.name = "dummy";
	k.type = KartType_1;
	m_karts.push_back(k);
	KartInfo k2("../resources/images/uvgreen.png");
	k2.name = "dummy";
	k2.type = KartType_2;
	m_karts.push_back(k2);
	KartInfo k3("../resources/images/uvblue.png");
	k3.type = KartType_3;
	k3.name = "dummy";
	m_karts.push_back(k3);

}

GameLogic::~GameLogic() {
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
	/*if(!m_map) {
		Util::LogManager::error("Cannot create a kart before the map has been selected");
		return nullptr;
	}*/
	return /*m_map->addKart(type)*/ nullptr;
}

Map* GameLogic::getMap() {
	return &m_map;
}

void GameLogic::update(float elapsed) {
	m_map.update(elapsed);
}

void GameLogic::loadMap(const std::string& map) {
	if(!m_map.loadFromFile(map)) {
		std::cerr << "Failed to load " << map << std::endl;
	}
}

void GameLogic::startRace() {
	m_clock.Restart();
}

void GameLogic::stopRace() {
	m_clock.Pause();
}

std::vector<KartInfos> GameLogic::getRaceResults() {
	return m_map.getResults();
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

const std::vector<MapInfo>& GameLogic::getMapList() {
	return m_maps;
}

const std::vector<KartInfo>& GameLogic::getKartList() {
	return m_karts;
}

const Util::Clock& GameLogic::getClock() const {
	return m_clock;
}