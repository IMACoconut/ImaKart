#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include <GameManager/gamestate.hpp>

class GameEngine
{
public:
	GameEngine(sf::RenderWindow& w) : m_window(w), m_running(true) {}
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

	sf::RenderWindow& getWindow() {
		return m_window;
	}

private:
	// the stack of states
	sf::RenderWindow& m_window;
	std::stack<GameState*> states;
	bool m_running;
	
};
