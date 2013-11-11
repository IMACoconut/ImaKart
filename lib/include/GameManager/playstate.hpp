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
	void Init();

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
	Graph::Shader s1, s2, s3;
	Graph::Heightmap mesh;
	Graph::Material hmtex;
	Graph::Scene scene;
	Graph::Camera cam;





private:
	

};