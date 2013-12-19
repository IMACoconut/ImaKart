#pragma once

class GameEngine;

class GameState
{
public:
	virtual void Init(GameEngine* game) = 0 ;
	virtual void Initialize (GameEngine* game) = 0;
	virtual void Release(GameEngine* game) = 0;
	virtual void Pause(GameEngine* game) = 0;
	virtual void Resume(GameEngine* game) = 0;
	virtual void HandleEvents(GameEngine* game) = 0;
	virtual void Update(GameEngine* game) = 0;
	virtual void Draw(GameEngine* game) = 0;

	
protected:
	GameState() { }
};



