#pragma once

#include <vector>
#include <stdint.h>

#include <glm/glm.hpp>
#include <Utility.hpp>
#include <Game/Map.hpp>
#include <Game/kart.hpp>

class Item;

class GameLogic {
public:
	static GameLogic& getInstance();
	
	Item* randomItem();
	Kart* createKart(KartType type);
	void loadMap(const std::string& map);
	void startRace();
	void endRace();
	bool isRaceFinished() const;

	void update(float elapsed);

	std::vector<KartInfo> getRaceResults();

private:
	GameLogic();
	~GameLogic();

	Map* m_map;
};