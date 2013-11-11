#include <Graphics.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>
#include <SFML/Graphics.hpp>
#include <tinyxml2/tinyxml2.h>

#include <Game/Entity.hpp>
#include <Game/Component.hpp>

#include <unistd.h>

#include <iostream>
#include <vector>


#include <GameManager/gameengine.hpp>
#include <GameManager/gameengine.hpp>
#include <GameManager/menustate.hpp>
#include <GameManager/playstate.hpp>

static const unsigned int FPS = 30;


int main(void) {

	tinyxml2::XMLDocument doc;
	doc.LoadFile("../resources/data/config.xml");

	uint32_t WINDOW_WIDTH = Util::FromString<uint32_t>(std::string(doc.FirstChildElement("window")->FirstChildElement("width")->GetText()));
	uint32_t WINDOW_HEIGHT = Util::FromString<uint32_t>(std::string(doc.FirstChildElement("window")->FirstChildElement("height")->GetText()));

	Util::LogManager::init();
	sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL4Imacs");
	//window.setFramerateLimit(FPS);

	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		Util::LogManager::error("Unable to initialize GLEW : "+Util::ToString(glewGetErrorString(glewCode)));
		return EXIT_FAILURE;
	}

	
	glClearColor(0.2,0.2,0.2,0);

	

	window.setMouseCursorVisible(false);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	Util::LogManager::notice("Running");

	sf::Clock frameTime, clock;
	int fps = 0;


	GameEngine game(window);
	
	// initialize the engine
	//MenuState m(window);

	// load the menu
	game.SetState(MenuState::getInstance());
	
	// main loop
	while ( game.Running() )
	{
		
		game.HandleEvents();
		game.Update();
		game.Draw();
	}

	return EXIT_SUCCESS;
}
