#include <Game/States/MultiMenu.hpp>
#include <GameManager/menustate.hpp>
#include <GameManager/playstate.hpp>
#include <GameManager/gameengine.hpp>

#include <iostream>
#include <GL/glew.h>
#include <TGUI/TGUI.hpp>

MultiMenu::MultiMenu(){
	

}

MultiMenu::~MultiMenu(){
	delete gui;
}

void MultiMenu::Init(GameEngine* game){
	gui = new tgui::Gui(game->getWindow());
	if (gui->setGlobalFont("../resources/widgets/DejaVuSans.ttf") == false)
        return;

	int center = (game->getWindow().getSize().x)/2;
    tgui::Button::Ptr create(*gui);
    create->load("../resources/widgets/Black.conf");
    create->setSize(260, 60);
    create->setPosition(center-((create->getSize().x)/2), 140);
    create->setText("Creer une Partie");
    create->bindCallback(tgui::Button::LeftMouseClicked);
    create->setCallbackId(1);

    tgui::Button::Ptr join(*gui);
    join->load("../resources/widgets/Black.conf");
    join->setSize(260, 60);
    join->setPosition(center-((join->getSize().x)/2), 240);
    join->setText("Rejoindre une Partie");
    join->bindCallback(tgui::Button::LeftMouseClicked);
    join->setCallbackId(2);

    tgui::Button::Ptr quit(*gui);
    quit->load("../resources/widgets/Black.conf");
    quit->setSize(260, 60);
    quit->setPosition(center-((quit->getSize().x)/2), 440);
    quit->setText("Retour");
    quit->bindCallback(tgui::Button::LeftMouseClicked);
    quit->setCallbackId(3);
}

void MultiMenu::Pause(){
	std::cout << "Pause" << std::endl;
}

void MultiMenu::Resume(){
	std::cout << "Resume" << std::endl;
}

void MultiMenu::Initialize(){

}

void MultiMenu::Release(){

}

void MultiMenu::Cleanup(){

}

void MultiMenu::HandleEvents(GameEngine* game){
	sf::Event e;
	sf::RenderWindow& window = game->getWindow();
	while(window.pollEvent(e)) {
		gui->handleEvent(e);
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
	while (gui->pollCallback(callback))
	{
		if (callback.id == 3)
			game->PopState();
	}
}

void MultiMenu::Update(GameEngine* game){

}

void MultiMenu::Draw(GameEngine* game){
	sf::RenderWindow& window = game->getWindow();
	window.clear();
	window.resetGLStates(); // On reset les matrices openGL avant de dessiner la gui
	gui->draw();
	window.display();
}