#pragma once
#include <Game/Entity.hpp>
#include <Game/Logic/Checkpoint.hpp>
#include <Game/Logic/ItemSpawn.hpp>
#include <Game/Logic/Startgrid.hpp>
#include <Graphics.hpp>
#include <string>
#include <vector>
#include <tuple>
#include <Utility.hpp>

class Kart;

typedef std::tuple<Kart*, int, int, bool> KartInfos;

class Map : public Entity, public Graph::Node{
public:
	Map() = default;
	~Map();

	void clear();

	bool loadFromFile(const std::string& file);

	bool loadIntoScene(Graph::Scene& scene);
	void draw();
	void drawCheckpoint();
	void hasFinishedLoop(Kart& k);
	void update(float elapsed);

	void addKart(Kart* k);
	std::vector<KartInfos> getResults();

	Graph::Heightmap* getHeightmap();

	const std::vector<Checkpoint*>& getCheckpoints() const {
		return m_checkpoints;
	}
	

private:
	void sortKartByPosition();

	Graph::Heightmap mesh;
	Graph::Material hmtex;
	Startgrid grid;
	std::vector<ItemSpawn*> m_itemSpawns;
	std::vector<KartInfos> m_karts;
	std::vector<Checkpoint*> m_checkpoints; 
	//void sortKartByPosition();

};