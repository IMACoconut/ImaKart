#pragma once
#include <stack>
#include <SFML/Graphics.hpp>

#include <Utility/Window.hpp>

class GameState;
class GameEngine
{
public:
	GameEngine(Util::Window& w) : m_window(w) {}

	GameState* GetCurrentState() { return ( !states.empty() ) ? states.top() : nullptr; }
	void PushState(GameState& state);
	void PopState();
	//void Update();
	bool Running() { return states.size(); }

	void HandleEvents();
	void Update();
	void Draw();

	void Quit();

	Util::Window& getWindow() {
		return m_window;
	}

private:
	// the stack of states
	Util::Window& m_window;
	std::stack<GameState*> states;	
};
