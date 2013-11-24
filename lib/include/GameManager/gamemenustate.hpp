#pragma once
#include <GameManager/gamestate.hpp>
#include <SFML/Graphics.hpp>


class GameEngine;
class GameMenuState: public GameState
{
public:
	GameMenuState();
	void Init(GameEngine* game);

	void Pause();
	void Resume();
	void Initialize();
	void Release();
	void Cleanup();
	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static GameMenuState& getInstance() {
		static GameMenuState s;
		return s;
	}


private:
	

};