#pragma once
#include <Game/Entity.hpp>
#include <Graphics.hpp>
#include <string>
#include <vector>

struct Checkpoint
{
	int x;
	int y;
};

class Map : public Entity, public Graph::Node{
public:
	Map() = default;
	~Map();

	bool loadFromFile(const std::string& file);

	bool loadIntoScene(Graph::Shader* s, Graph::Scene& scene);
	void draw();
	void drawCheckpoint();

private:
	Graph::Heightmap mesh;
	Graph::Material hmtex;
	std::vector<Graph::Mesh*> meshCheckpoint; 

};