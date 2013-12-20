#pragma once

#include <GameManager/GameState.hpp>
#include <GameManager/GameEngine.hpp>
#include <Game/States/LoadingState.hpp>
#include <SFML/Graphics.hpp>
#include <Game/Kart.hpp>
#include <Game/Map.hpp>

class GameEngine;
class Game : public GameState
{
private:
	Graph::Heightmap mesh;
	Graph::Mesh mesh2;
	Graph::Material hmtex;
	Graph::Skydome sky;
	Graph::PointLight light;
	Graph::PointLight light4;
	Graph::SpotLight light2;
	Graph::DirectionalLight light3;
	Graph::Scene scene;
	Graph::Camera* cam;
	sf::Clock frameTime, clock, timeOfDay;
	int fps = 0;
	Map m;
	Kart k;
	GameEngine* m_game;
	LoadingState<Game> m_loader;
	bool tourne;

public:
	Game();
	~Game();


	void Init(GameEngine* game);
	void load();

	void Pause(GameEngine* game);
	void Resume(GameEngine* game);
	void Initialize(GameEngine* game);
	void Release(GameEngine* game);
	void Cleanup(GameEngine* game);
	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static Game& getInstance() {
		static Game s;
		return s;
	}
};