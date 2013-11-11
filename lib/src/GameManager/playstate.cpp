#include <GameManager/playstate.hpp>
#include <GameManager/gameengine.hpp>
#include <iostream>
#include <GL/glew.h>


PlayState::PlayState() {
	

}

void PlayState::Init()
{
	

}

void PlayState::Initialize()
{
	

}

void PlayState::Release()
{
	

}

void PlayState::Cleanup()
{
	

}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}

void PlayState::HandleEvents(GameEngine* game)
{
	sf::Event e;
	sf::Window& window = game->getWindow();
		while(window.pollEvent(e)) {
			switch(e.type) {
				
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseMoved:
					//std::cout << "moving !" << std::endl;	
					break;
				case sf::Event::KeyPressed:
					switch(e.key.code) {
						case sf::Keyboard::Key::Escape:
							game->PopState();
							break;
						case sf::Keyboard::Key::Space:
							std::cout << "Play State" << std::endl;	
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

void PlayState::Update(GameEngine* game) 
{

}

void PlayState::Draw(GameEngine* game) 
{
	// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
	sf::Window& window = game->getWindow();
	window.display();
	
}

