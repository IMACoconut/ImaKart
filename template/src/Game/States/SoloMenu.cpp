#include <Game/States/SoloMenu.hpp>
#include <Game/States/KartSelectMenu.hpp>
#include <GameManager/GameEngine.hpp>

#include <iostream>
#include <GL/glew.h>
#include <TGUI/TGUI.hpp>

SoloMenu::SoloMenu() :
	maps(GameLogic::getInstance().getMapList())
{

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

    listBox = tgui::ListBox::Ptr(gui);
    listBox->load("../resources/widgets/Black.conf");
    listBox->setSize(240, 300);
    listBox->setItemHeight(20);
    listBox->setPosition(40, 40);
    listBox->bindCallback(tgui::ListBox::ItemSelected);
    listBox->setCallbackId(2);


    for(auto m: maps) {
    	listBox->addItem(m.name);
    }

    picture = tgui::Picture::Ptr(gui);

    setSelectedMap(0);
    
    // Create the Quitter button
    tgui::Button::Ptr quit(gui);
    quit->load("../resources/widgets/Black.conf");
    quit->setSize(240, 60);
    quit->setPosition(40, 440);
    quit->setText("Retour");
    quit->bindCallback(tgui::Button::LeftMouseClicked);
    quit->setCallbackId(3);


	game->getWindow().setMouseCursorVisible(true);
}

void SoloMenu::Initialize(GameEngine* game){

}

void SoloMenu::Release(GameEngine* game){
	auto& gui = game->getWindow().getGui();
	gui.removeAllWidgets();
}

void SoloMenu::Cleanup(GameEngine* game){
	auto& gui = game->getWindow().getGui();
	gui.removeAllWidgets();
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

					case sf::Keyboard::Key::Return:
						// Set kart selection menu
						GameLogic::getInstance().loadMap(maps[listBox->getSelectedItemIndex()].file.getFullPath());
						game->PopState();
						game->PushState(KartSelectMenu::getInstance());
						break;
					case sf::Keyboard::Key::Up:
						{
							int p = listBox->getSelectedItemIndex();
							setSelectedMap(p-1);
						}
						break;
					case sf::Keyboard::Key::Down:
						{
							int p = listBox->getSelectedItemIndex();
							setSelectedMap(p+1);
						}
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
		else if(callback.id == 2)
		{
			int p = listBox->getSelectedItemIndex();
			setSelectedMap(p);
		}
	}
}

void SoloMenu::Update(GameEngine* game){

}

void SoloMenu::Draw(GameEngine* game){
	Util::Window& window = game->getWindow();
	window.clear();
	window.display();
}

void SoloMenu::setSelectedMap(int p) {
	p = (p<0 || p >= maps.size()) ? 0 : p;

	listBox->setSelectedItem(p);
	picture->load(maps[p].file.getDirectory()+"/"+maps[p].image);
	picture->setSize(400,400);
	picture->setPosition(400,100);
}