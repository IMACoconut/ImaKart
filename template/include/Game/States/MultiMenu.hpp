#pragma once

#include <GameManager/GameState.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class GameEngine;
class MultiMenu : public GameState{
private:
	
public:
	MultiMenu();
	~MultiMenu();
	
	void Init(GameEngine* game);

	void Pause(GameEngine* game);
	void Resume(GameEngine* game);
	void Initialize(GameEngine* game);
	void Release(GameEngine* game);
	void Cleanup(GameEngine* game);
	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	static MultiMenu& getInstance() {
		static MultiMenu s;
		return s;
	}

	
};