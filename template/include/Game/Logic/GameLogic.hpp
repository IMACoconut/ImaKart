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

class GameLogic {
public:
	static GameLogic& getInstance();
	
	Item* randomItem();
	Kart* createKart(KartType type);

	void setCamera(Graph::Camera* cam);
	void loadMap(const std::string& map);
	void startRace();
	void endRace();
	bool isRaceFinished() const;

	void update(float elapsed);

	Util::XboxInput& getXboxInput();
	Util::MouseInput& getMouseInput();
	std::vector<KartInfo> getRaceResults();

private:
	GameLogic();
	~GameLogic();

	Map* m_map;
	Graph::Camera* m_camera;
};