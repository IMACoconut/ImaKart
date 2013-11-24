#pragma once
#include <GameManager/gamestate.hpp>
#include <Graphics.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>
#include <SFML/Graphics.hpp>


class GameEngine;
class PlayState: public GameState
{
public:
	PlayState();
	void Init(GameEngine* game);

	void Pause();
	void Resume();
	void Initialize();
	void Release();
	void Cleanup();
	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static PlayState& getInstance() {
		static PlayState s;
		return s;
	}
	Graph::Heightmap mesh;
	Graph::Material hmtex;
	Graph::Mesh mesh3;
	Graph::Skydome sky;	
	Graph::DirectionalLight light;
	Graph::Scene scene;
	Graph::Camera cam;
	Graph::Shader* skyShader;
	Graph::Shader* celShad ;
	

	sf::Clock frameTime, clock;
	int fps = 0;





private:
	

};