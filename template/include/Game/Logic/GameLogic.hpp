#pragma once

#include <vector>
#include <stdint.h>

#include <glm/glm.hpp>
#include <Utility.hpp>
#include <Game/Map.hpp>
#include <Game/Kart.hpp>

class Item;

namespace Util {
	class XboxInput;
	class MouseInput;
}
namespace Graph {
	class Camera;
}

struct MapInfo {
	MapInfo(const std::string& file) :
		file(file)
	{}

	Util::FilePath file;
	std::string name, image;
};

struct KartInfo {
	KartInfo(const std::string& file) :
		file(file)
	{}

	Util::FilePath file;
	std::string name;
	KartType type;
};

class GameLogic {
public:
	static GameLogic& getInstance();
	
	Item* randomItem();
	Kart* createKart(KartType type);
	Map* getMap();

	void setCamera(Graph::Camera* cam);
	void loadMap(const std::string& map);
	void startRace();
	void endRace();
	bool isRaceFinished() const;

	void update(float elapsed);

	Util::XboxInput& getXboxInput();
	Util::MouseInput& getMouseInput();
	std::vector<KartInfos> getRaceResults();

	const std::vector<MapInfo>& getMapList();
	const std::vector<KartInfo>& getKartList();

private:
	GameLogic();
	~GameLogic();

	Map m_map;
	Graph::Camera* m_camera;
	std::vector<MapInfo> m_maps;
	std::vector<KartInfo> m_karts;
};