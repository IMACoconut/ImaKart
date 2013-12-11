#pragma once

#include <GameManager/gamestate.hpp>
#include <GameManager/gameengine.hpp>
#include <SFML/Graphics.hpp>
#include <Game/kart.hpp>
#include <Game/map.hpp>

class GameEngine;
class Game : public GameState
{
private:
	Graph::Heightmap mesh;
	Graph::Material hmtex;
	Graph::Skydome sky;
	Graph::PointLight light;
	Graph::PointLight light4;
	Graph::SpotLight light2;
	Graph::DirectionalLight light3;
	Graph::Scene scene;
	Graph::Camera cam;
	sf::Clock frameTime, clock;
	int fps = 0;
	Map m;
	Kart k;

public:
	Game();
	~Game();


	void Init(GameEngine* game);

	void Pause();
	void Resume();
	void Initialize();
	void Release();
	void Cleanup();
	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static Game& getInstance() {
		static Game s;
		return s;
	}
};