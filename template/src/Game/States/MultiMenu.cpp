#include <Game/States/MultiMenu.hpp>
#include <GameManager/GameEngine.hpp>

#include <iostream>
#include <GL/glew.h>
#include <TGUI/TGUI.hpp>

MultiMenu::MultiMenu(){
	

}

MultiMenu::~MultiMenu(){
}

void MultiMenu::Init(GameEngine* game){
	Resume(game);
}

void MultiMenu::Pause(GameEngine* game){
	auto& gui = game->getWindow().getGui();
	gui.removeAllWidgets();
}

void MultiMenu::Resume(GameEngine* game){
	auto& gui = game->getWindow().getGui();
	int center = (game->getWindow().getSize().x)/2;
    tgui::Button::Ptr create(gui);
    create->load("../resources/widgets/Black.conf");
    create->setSize(260, 60);
    create->setPosition(center-((create->getSize().x)/2), 140);
    create->setText("Creer une Partie");
    create->bindCallback(tgui::Button::LeftMouseClicked);
    create->setCallbackId(1);

    tgui::Button::Ptr join(gui);
    join->load("../resources/widgets/Black.conf");
    join->setSize(260, 60);
    join->setPosition(center-((join->getSize().x)/2), 240);
    join->setText("Rejoindre une Partie");
    join->bindCallback(tgui::Button::LeftMouseClicked);
    join->setCallbackId(2);

    tgui::Button::Ptr quit(gui);
    quit->load("../resources/widgets/Black.conf");
    quit->setSize(260, 60);
    quit->setPosition(center-((quit->getSize().x)/2), 440);
    quit->setText("Retour");
    quit->bindCallback(tgui::Button::LeftMouseClicked);
    quit->setCallbackId(3);
	game->getWindow().setMouseCursorVisible(true);
}

void MultiMenu::Initialize(GameEngine* game){

}

void MultiMenu::Release(GameEngine* game){

}

void MultiMenu::Cleanup(GameEngine* game){

}

void MultiMenu::HandleEvents(GameEngine* game){
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
	}
}

void MultiMenu::Update(GameEngine* game){

}

void MultiMenu::Draw(GameEngine* game){
	auto& window = game->getWindow();
	window.clear();
	window.display();
}