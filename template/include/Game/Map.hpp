#pragma once
#include <Game/Entity.hpp>
#include <Game/Logic/Checkpoint.hpp>
#include <Game/Logic/ItemSpawn.hpp>
#include <Graphics.hpp>
#include <string>
#include <vector>
#include <tuple>
#include <Utility.hpp>
#include <Physics/Collidable.hpp>

class Kart;

typedef std::tuple<Kart*, Util::Clock, int, bool> KartInfo;

class Map : public Entity{
public:
	Map() ;
	~Map();

	bool loadFromFile(const std::string& file);

	bool loadIntoScene(Graph::Scene& scene);
	void draw();
	void drawCheckpoint();
	void hasFinishedLoop(Kart& k);
	void update(float elapsed);

	void addKart(Kart* k);
	std::vector<KartInfo> getResults();

	Graph::Heightmap* getHeightmap();

	std::vector<Checkpoint*> m_checkpoints; 
	Phys::Collidable collidable;

private:
	void sortKartByPosition();

	Graph::Heightmap mesh;
	Graph::Material hmtex;
	//Startgrid grid;
	std::vector<ItemSpawn*> m_itemSpawns;
	std::vector<KartInfo> m_karts;

	//void sortKartByPosition();

};