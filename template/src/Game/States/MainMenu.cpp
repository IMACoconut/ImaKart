#include <Game/States/MainMenu.hpp>
#include <Game/States/SoloMenu.hpp>
#include <Game/States/MultiMenu.hpp>
#include <GameManager/menustate.hpp>
#include <GameManager/playstate.hpp>
#include <GameManager/gameengine.hpp>

#include <iostream>
#include <GL/glew.h>
#include <TGUI/TGUI.hpp>

MainMenu::MainMenu(){
	

}

MainMenu::~MainMenu(){
	delete gui;
}

void MainMenu::Init(GameEngine* game){
	gui = new tgui::Gui(game->getWindow());
	if (gui->setGlobalFont("../resources/widgets/DejaVuSans.ttf") == false)
        return;

    int center = (game->getWindow().getSize().x)/2;
    // Create the Partie Solo button
    tgui::Button::Ptr solo(*gui);
    solo->load("../resources/widgets/Black.conf");
    solo->setSize(260, 60);
    solo->setPosition(center-((solo->getSize().x)/2), 140);
    solo->setText("Partie Solo");
    solo->bindCallback(tgui::Button::LeftMouseClicked);
    solo->setCallbackId(1);

    // Create the Partie Multi button
    tgui::Button::Ptr multi(*gui);
    multi->load("../resources/widgets/Black.conf");
    multi->setSize(260, 60);
    multi->setPosition(center-((multi->getSize().x)/2), 240);
    multi->setText("Partie Multi");
    multi->bindCallback(tgui::Button::LeftMouseClicked);
    multi->setCallbackId(2);

    // Create the Quitter button
    tgui::Button::Ptr quit(*gui);
    quit->load("../resources/widgets/Black.conf");
    quit->setSize(260, 60);
    quit->setPosition(center-((quit->getSize().x)/2), 440);
    quit->setText("Quitter");
    quit->bindCallback(tgui::Button::LeftMouseClicked);
    quit->setCallbackId(3);
}

void MainMenu::Pause(){
	std::cout << "Pause" << std::endl;
}

void MainMenu::Resume(){
	std::cout << "Resume" << std::endl;
}

void MainMenu::Initialize(){

}

void MainMenu::Release(){

}

void MainMenu::Cleanup(){

}

void MainMenu::HandleEvents(GameEngine* game){
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
						game->Quit();
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
			game->Quit();
		else if(callback.id == 1)
			//Menu Solo
			game->PushState(SoloMenu::getInstance());
		else if(callback.id == 2)
			//Menu Multi
			game->PushState(MultiMenu::getInstance());
	}
}

void MainMenu::Update(GameEngine* game){

}

void MainMenu::Draw(GameEngine* game){
	sf::RenderWindow& window = game->getWindow();
	window.clear();
	window.resetGLStates(); // On reset les matrices openGL avant de dessiner la gui
	gui->draw();
	window.display();
}