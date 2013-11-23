#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include <GameManager/gamestate.hpp>

class GameEngine
{
public:
	GameEngine(sf::Window& w) : m_window(w) {}
	void Init();
	GameState* GetCurrentState() { return ( !states.empty() ) ? states.top() : nullptr; }
	void SetState(GameState& state);
	void PushState(GameState& state);
	void PopState();
	//void Update();
	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	void HandleEvents();
	void Update();
	void Draw();

	sf::Window& getWindow() {
		return m_window;
	}

private:
	// the stack of states
	sf::Window& m_window;
	std::stack<GameState*> states;
	bool m_running;
	
};
