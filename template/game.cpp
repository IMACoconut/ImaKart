#include <Graphics.hpp>
#include <Utility.hpp>
#include <Network.hpp>
#include <Game/Network/NetworkTCP.hpp>
#include <Game/Network/NetworkUDP.hpp>

#include <SFML/Graphics.hpp>
#include <tinyxml2/tinyxml2.h>

#include <Game/Entity.hpp>
#include <Game/Component.hpp>
#include <Game/Map.hpp>
#include <Game/Kart.hpp>
#include <GameManager/GameEngine.hpp>
#include <Game/States/MainMenu.hpp>
#include <Graphics/Scene/OrbitCamera.hpp>

#include <unistd.h>

#include <iostream>
#include <vector>

#define THEME_CONFIG_FILE "../resources/widgets/Black.conf"

static const unsigned int FPS = 30;

int main(void) {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("../resources/data/config.xml");

	uint32_t WINDOW_WIDTH = Util::FromString<uint32_t>(std::string(doc.FirstChildElement("window")->FirstChildElement("width")->GetText()));
	uint32_t WINDOW_HEIGHT = Util::FromString<uint32_t>(std::string(doc.FirstChildElement("window")->FirstChildElement("height")->GetText()));

	Util::LogManager::init();
	NzNetwork::Initialize();

	Util::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL4Imacs");
	if (window.getGui().setGlobalFont("../resources/widgets/DejaVuSans.ttf") == false)
		return -1;
	
	GLenum g = glewInit();
	if(g != GLEW_OK) {
		Util::LogManager::error("Unable to initialize GLEW : "+Util::ToString(glewGetErrorString(g)));
		return EXIT_FAILURE;
	}

	GameEngine engine(window);
	engine.PushState(MainMenu::getInstance());

	while(engine.Running()){
		engine.HandleEvents();
		engine.Update();
		engine.Draw();
	}

	NzNetwork::Uninitialize();
	return EXIT_SUCCESS;	
}
