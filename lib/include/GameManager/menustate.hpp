/*#pragma once
#include <GameManager/gamestate.hpp>
#include <SFML/Graphics.hpp>


class GameEngine;
class MenuState: public GameState
{
public:
	MenuState();
	void Init(GameEngine* game);

	void Pause();
	void Resume();
	void Initialize();
	void Release();
	void Cleanup();
	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static MenuState& getInstance() {
		static MenuState s;
		return s;
	}


private:
	

};*/