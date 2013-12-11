#pragma once

#include <GameManager/GameState.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class GameEngine;
class MainMenu : public GameState{
private:

public:
	MainMenu();
	~MainMenu();
	
	void Init(GameEngine* game);

	void Pause(GameEngine* game);
	void Resume(GameEngine* game);
	void Initialize(GameEngine* game);
	void Release(GameEngine* game);
	void Cleanup(GameEngine* game);
	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static MainMenu& getInstance() {
		static MainMenu s;
		return s;
	}

	
};