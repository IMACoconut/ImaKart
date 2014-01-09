#include <Game/States/KartSelectMenu.hpp>
#include <Game/States/Game.hpp>
#include <GameManager/GameEngine.hpp>

#include <iostream>
#include <GL/glew.h>
#include <TGUI/TGUI.hpp>

KartSelectMenu::KartSelectMenu() :
	karts(GameLogic::getInstance().getKartList())
{

}

KartSelectMenu::~KartSelectMenu(){

}

void KartSelectMenu::Init(GameEngine* game){
	Resume(game);
}

void KartSelectMenu::Pause(GameEngine* game){
	auto& gui = game->getWindow().getGui();
	gui.removeAllWidgets();
}

void KartSelectMenu::Resume(GameEngine* game){
	auto& gui = game->getWindow().getGui();
	int center = (game->getWindow().getSize().x)/2;

	listBox = tgui::ListBox::Ptr(gui);
    listBox->load("../resources/widgets/Black.conf");
    listBox->setSize(240, 300);
    listBox->setItemHeight(20);
    listBox->setPosition(40, 40);
    listBox->bindCallback(tgui::ListBox::ItemSelected);
    listBox->setCallbackId(2);


    for(auto m: karts) {
    	listBox->addItem(m.name);
    }
    listBox->setSelectedItem(0);

    picture = tgui::Picture::Ptr(gui);
    setSelectedKart(0);

	game->getWindow().setMouseCursorVisible(true);
}

void KartSelectMenu::Initialize(GameEngine* game){

}

void KartSelectMenu::Release(GameEngine* game){
	auto& gui = game->getWindow().getGui();
	gui.removeAllWidgets();
}

void KartSelectMenu::Cleanup(GameEngine* game){
	auto& gui = game->getWindow().getGui();
	gui.removeAllWidgets();
}

void KartSelectMenu::HandleEvents(GameEngine* game){
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

						game->PopState();
						game->PushState(Game::getInstance());
						break;
					case sf::Keyboard::Key::Up:
						{
							int p = listBox->getSelectedItemIndex();
							setSelectedKart(p-1);
						}
						break;
					case sf::Keyboard::Key::Down:
						{
							int p = listBox->getSelectedItemIndex();
							setSelectedKart(p+1);
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
			setSelectedKart(p);
		}
	}
}

void KartSelectMenu::Update(GameEngine* game){

}

void KartSelectMenu::Draw(GameEngine* game){
	Util::Window& window = game->getWindow();
	window.clear();
	window.display();
}

void KartSelectMenu::setSelectedKart(int p) {
	p = (p<0 || p >= karts.size()) ? 0 : p;

	listBox->setSelectedItem(p);
	picture->load(karts[p].file.getFullPath());
	picture->setSize(400,400);
	picture->setPosition(400,100);
}