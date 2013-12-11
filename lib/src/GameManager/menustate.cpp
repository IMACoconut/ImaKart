#include <GameManager/menustate.hpp>
#include <GameManager/playstate.hpp>
#include <GameManager/gameengine.hpp>
#include <iostream>
#include <GL/glew.h>


MenuState::MenuState() {

}

void MenuState::Init(GameEngine* game)
{
	

}

void MenuState::Initialize()
{
	

}

void MenuState::Release()
{
	

}

void MenuState::Cleanup()
{
	

}

void MenuState::Pause()
{
	std::cout << "Pause" << std::endl;
}

void MenuState::Resume()
{
	std::cout << "Resume" << std::endl;
}

void MenuState::HandleEvents(GameEngine* game)
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
							game->Quit();
							break;
						case sf::Keyboard::Key::Space:
							std::cout << "Menu State -> Play State" << std::endl;	
							
							game->PushState(PlayState::getInstance());


						break;
						case sf::Keyboard::Key::A:
							std::cout << "Menu State" << std::endl;	
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

void MenuState::Update(GameEngine* game) 
{

}

void MenuState::Draw(GameEngine* game) 
{
	// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
	sf::Window& window = game->getWindow();

	window.display();
	
}

