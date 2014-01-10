#pragma once

#include <GameManager/GameState.hpp>
#include <Game/Logic/GameLogic.hpp>

#include <TGUI/TGUI.hpp>

class GameEngine;
class KartSelectMenu : public GameState{
private:
	const std::vector<KartInfo>& karts;
	tgui::ListBox::Ptr listBox;
	tgui::Picture::Ptr picture;

	KartSelectMenu();
	~KartSelectMenu();

public:	
	void Init(GameEngine* game);

	void Pause(GameEngine* game);
	void Resume(GameEngine* game);
	void Initialize(GameEngine* game);
	void Release(GameEngine* game);
	void Cleanup(GameEngine* game);
	void HandleEvents(GameEngine* game);
	void Update(GameEngine* game);
	void Draw(GameEngine* game);

	void setSelectedKart(int p);

	static KartSelectMenu& getInstance() {
		static KartSelectMenu s;
		return s;
	}

	
};