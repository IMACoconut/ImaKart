#pragma once
#include <Game/Entity.hpp>
#include <Game/Logic/Checkpoint.hpp>
#include <Game/Logic/ItemSpawn.hpp>
#include <Graphics.hpp>
#include <string>
#include <vector>
#include <tuple>
#include <Utility.hpp>

class Kart;
typedef std::tuple<Kart*, Util::Clock, int, bool> KartInfo;

class Map : public Entity, public Graph::Node{
public:
	Map() = default;
	~Map();

	bool loadFromFile(const std::string& file);

	bool loadIntoScene(Graph::Scene& scene);
	void draw();
	void drawCheckpoint();
	void hasFinishedLoop(Kart& k);
	void update(float elapsed);

	Kart* addKart(KartType type);
	std::vector<KartInfo> getResults();

	Graph::Heightmap* getHeightmap();


private:
	Graph::Heightmap mesh;
	Graph::Material hmtex;
	std::vector<Checkpoint*> m_checkpoints; 
	std::vector<ItemSpawn*> m_itemSpawns;
	std::vector<KartInfo> m_karts;

};