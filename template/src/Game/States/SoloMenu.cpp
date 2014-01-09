#include <Game/States/SoloMenu.hpp>
#include <Game/States/Game.hpp>
#include <GameManager/GameEngine.hpp>

#include <iostream>
#include <GL/glew.h>
#include <TGUI/TGUI.hpp>

SoloMenu::SoloMenu(){
	

}

SoloMenu::~SoloMenu(){

}

void SoloMenu::Init(GameEngine* game){
	Resume(game);
}

void SoloMenu::Pause(GameEngine* game){
	auto& gui = game->getWindow().getGui();
	gui.removeAllWidgets();
}

void SoloMenu::Resume(GameEngine* game){
	auto& gui = game->getWindow().getGui();
	int center = (game->getWindow().getSize().x)/2;
    tgui::Button::Ptr map(gui);
    map->load("../resources/widgets/Black.conf");
    map->setSize(260, 60);
    map->setPosition(center-((map->getSize().x)/2), 140);
    map->setText("Choisir une map");
    map->bindCallback(tgui::Button::LeftMouseClicked);
    map->setCallbackId(1);

    // Create the Partie Multi button
    tgui::Button::Ptr kart(gui);
    kart->load("../resources/widgets/Black.conf");
    kart->setSize(260, 60);
    kart->setPosition(center-((kart->getSize().x)/2), 240);
    kart->setText("Choisir un Kart");
    kart->bindCallback(tgui::Button::LeftMouseClicked);
    kart->setCallbackId(2);

    // Create the Quitter button
    tgui::Button::Ptr quit(gui);
    quit->load("../resources/widgets/Black.conf");
    quit->setSize(260, 60);
    quit->setPosition(center-((quit->getSize().x)/2), 440);
    quit->setText("Retour");
    quit->bindCallback(tgui::Button::LeftMouseClicked);
    quit->setCallbackId(3);


	game->getWindow().setMouseCursorVisible(true);
}

void SoloMenu::Initialize(GameEngine* game){

}

void SoloMenu::Release(GameEngine* game){

}

void SoloMenu::Cleanup(GameEngine* game){

}

void SoloMenu::HandleEvents(GameEngine* game){
	sf::Event e;
	auto& window = game->getWindow();
	auto& gui = game->getWindow().getGui();
	while(window.pollEvent(e)) {
		gui.handleEvent(e);
		switch(e.type) {
			case sf::Event::Closed:
				game->Quit();
				break;
			case sf::Event::MouseMoved:
				
				break;
			case sf::Event::KeyPressed:
				switch(e.key.code) {
					case sf::Keyboard::Key::Escape:
						game->PopState();
						break;
					case sf::Keyboard::Key::Space:


					break;

					default:
						break;
				}
				break;
			default:
				break;
		}
	}

	tgui::Callback callback;
	while (gui.pollCallback(callback))
	{
		if (callback.id == 3)
			game->PopState();
		else if(callback.id == 1)
			game->PushState(Game::getInstance());

	}
}

void SoloMenu::Update(GameEngine* game){

}

void SoloMenu::Draw(GameEngine* game){
	Util::Window& window = game->getWindow();
	window.clear();
	window.display();
}