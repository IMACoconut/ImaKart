#pragma once

class GameEngine;

class GameState
{
public:
	virtual void Init(GameEngine* game) = 0 ;
	virtual void Initialize () = 0;
	virtual void Release() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void HandleEvents(GameEngine* game) = 0;
	virtual void Update(GameEngine* game) = 0;
	virtual void Draw(GameEngine* game) = 0;

	
protected:
	GameState() { }
};



