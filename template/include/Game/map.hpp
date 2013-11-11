#pragma once
#include <Game/Entity.hpp>
#include <Graphics/Heightmap.hpp>
#include <Graphics/Material.hpp>
#include <string>

struct Checkpoint
{
	int x;
	int y;
};

class Map : public Entity{
public:
	Map() = default;
	~Map() = default;

	bool loadFromFile(const std::string& file);

	bool loadIntoScene(Graph::Shader* s);
	void draw();
	void drawCheckpoint();

private:
	Graph::Heightmap mesh;
	Graph::Material hmtex;
	Graph::Mesh meshCheckpoint; 



};