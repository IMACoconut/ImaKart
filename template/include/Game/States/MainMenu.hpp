#pragma once

#include <GameManager/gamestate.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class GameEngine;
class MainMenu : public GameState{
private:
	tgui::Gui* gui;

public:
	MainMenu();
	~MainMenu();
	
	void Init(GameEngine* game);

	void Pause();
	void Resume();
	void Initialize();
	void Release();
	void Cleanup();
	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static MainMenu& getInstance() {
		static MainMenu s;
		return s;
	}

	
};