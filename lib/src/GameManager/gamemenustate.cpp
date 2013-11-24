#include <GameManager/gamemenustate.hpp>
#include <GameManager/menustate.hpp>
#include <GameManager/gameengine.hpp>
#include <iostream>
#include <GL/glew.h>


GameMenuState::GameMenuState() {

}

void GameMenuState::Init(GameEngine* game)
{
	

}

void GameMenuState::Initialize()
{
	

}

void GameMenuState::Release()
{
	

}

void GameMenuState::Cleanup()
{
	

}

void GameMenuState::Pause()
{
	std::cout << "Pause" << std::endl;
}

void GameMenuState::Resume()
{
	std::cout << "Resume" << std::endl;
}

void GameMenuState::HandleEvents(GameEngine* game)
{
	sf::Event e;
	sf::Window& window = game->getWindow();
		while(window.pollEvent(e)) {
			switch(e.type) {
				
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseMoved:
					
					break;
				case sf::Event::KeyPressed:
					switch(e.key.code) {
						case sf::Keyboard::Key::Escape:
							game->SetState(MenuState::getInstance());
							break;
						case sf::Keyboard::Key::Space:
							std::cout << "Menu in-game" << std::endl;	
							
							game->PopState();


						break;
						case sf::Keyboard::Key::A:
							std::cout << "Menu in-game" << std::endl;	
						break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}
}

void GameMenuState::Update(GameEngine* game) 
{

}

void GameMenuState::Draw(GameEngine* game) 
{
	// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
	sf::Window& window = game->getWindow();

	window.display();
	
}

