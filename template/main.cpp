#include <Graphics.hpp>
#include <Utility.hpp>
#include <SFML/Graphics.hpp>
#include <tinyxml2/tinyxml2.h>

#include <Game/Entity.hpp>
#include <Game/Component.hpp>
#include <Game/map.hpp>
#include <Game/kart.hpp>

#include <Physics/AABB3D.hpp>

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

	

	Graph::Shader* lightPoint = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightPoint", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightPoint.frag");
	Graph::Shader* lightDirectional = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightDirectional", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightDirectional.frag");
	Graph::Shader* lightSpot = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightSpot", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightSpot.frag");

	glClearColor(0,0,0,0);

	Graph::PointLight light;
	light.setColor(glm::vec3(1,1, 0.419f));
	light.setIntensity(3.f);
	light.setRadius(1000.f);
	light.setPosition(glm::vec3(128*16,100.f*16,128*16));
	light.setShader(lightPoint);

	Graph::PointLight light4;
	light4.setColor(glm::vec3(.5,0.03, 0));
	light4.setIntensity(10.f);
	light4.setRadius(1000.f);
	light4.setPosition(glm::vec3(128*16,100.f*16,128*16));
	light4.setShader(lightPoint);

	Graph::SpotLight light2;
	light2.setColor(glm::vec3(1,0, 0));
	light2.setIntensity(3.f);
	light2.setRadius(100.f);
	light2.setPosition(glm::vec3(128*16,100.f*16,128*14));
	light2.setDirection(glm::vec3(0,-100*16,-100*16));
	light2.setShader(lightSpot);

	Graph::DirectionalLight light3;
	light3.setColor(glm::vec3(1,1,1));
	light3.setIntensity(.4f);
	light3.setPosition(glm::vec3(0,-9000,0));
	light3.setShader(lightDirectional);
	scene.setBackground(&sky);
	//scene.addMesh(&mesh3);
	scene.addLight(&light2);
	scene.addLight(&light3);
	scene.addLight(&light4);

	Map m;
	m.loadFromFile("../resources/maps/dummy2/map.xml");
	m.loadIntoScene(celShad, scene);

	Kart k;
	k.loadIntoScene(scene);


	window.setMouseCursorVisible(false);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	Util::LogManager::notice("Running");

	sf::Clock frameTime, clock;
	std::string fpsStr = "0 FPS";
	int fps = 0;
		auto elapsed = clock.getElapsedTime().asMilliseconds() *0.0001f;

			cam.move(cam.left()*(elapsed));
			cam.move(cam.right()*(elapsed));

	GameEngine game(window);
			cam.move(cam.forward()*(elapsed));
			cam.move(cam.backward()*(elapsed));

		

		k.update(elapsed);
	
	// initialize the engine
	//MenuState m(window);
			fpsStr = Util::ToString(fps)+"FPS";
			window.setTitle("ImaKart "+fpsStr);
			
		//window.setTitle("ImaKart "+fpsStr+ " "+Util::ToString(cam.getPosition().x)+"X " + Util::ToString(cam.getPosition().y)+"Y "+Util::ToString(cam.getPosition().z)+"Z");
	// load the menu
	game.SetState(MenuState::getInstance());
	
		
		//light3.setPosition(glm::vec3(sin(elapsed)*9000,cos(elapsed)*9000,0));
		light.setPosition(glm::vec3(128*16+sin(elapsed*3)*128*3,100*16,128*16+cos(elapsed*3)*128*3));
		light2.setPosition(glm::vec3(128*16,100*16+sin(elapsed*5),128*14+cos(elapsed*5)*128*3));
		light4.setPosition(glm::vec3(128*14+sin(elapsed*10)*128*3,100*16,128*16+cos(elapsed*10)*128*3));
		
		game.HandleEvents();
		game.Update();
		game.Draw();
	}

	return EXIT_SUCCESS;
}
