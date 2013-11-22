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

	
	Graph::Shader* skyShader = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"skyBox", "../resources/shaders/skybox.vert", "../resources/shaders/skybox.frag");
	Graph::Shader* celShad = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"celShad", "../resources/shaders/textured.vert", "../resources/shaders/textured.frag");

	Graph::Shader* lightPoint = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightPoint", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightPoint.frag");
	Graph::Shader* lightDirectional = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightDirectional", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightDirectional.frag");
	Graph::Shader* lightSpot = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightSpot", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightSpot.frag");

	glClearColor(0,0,0,0);

	Graph::Skydome sky;
	sky.setShader(skyShader);
	
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
	//s.bind();*/
	Graph::Scene scene;
	Graph::Camera cam;
	cam.setAspect(WINDOW_WIDTH, WINDOW_HEIGHT);
	scene.setCamera(&cam);
	scene.setBackground(&sky);
	//scene.addMesh(&mesh3);
	//scene.addLight(&light);
	scene.addLight(&light2);
	scene.addLight(&light3);
	//scene.addLight(&light4);

	Map m;
	m.loadFromFile("../resources/maps/dummy2/map.xml");
	m.loadIntoScene(celShad, scene);

	Kart k;
	k.loadIntoScene(scene);


	int old_x = WINDOW_WIDTH/2;
	int old_y = WINDOW_HEIGHT/2;

	window.setMouseCursorVisible(false);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	Util::LogManager::notice("Running");

	sf::Clock frameTime, clock;
	std::string fpsStr = "0 FPS";
	int fps = 0;
	while(window.isOpen()) {

		sf::Event e;
		while(window.pollEvent(e)) {
			switch(e.type) {
				
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseMoved:
					if(e.mouseMove.x < 0.001f && e.mouseMove.y < 0.001f)
						break;
					
					cam.rotate(e.mouseMove.x - old_x,e.mouseMove.y-old_y);

					break;
				case sf::Event::KeyPressed:
					switch(e.key.code) {
						case sf::Keyboard::Key::Escape:
							window.close();
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}
		auto elapsed = clock.getElapsedTime().asMilliseconds() *0.0001f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			cam.move(cam.left()*(elapsed));
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			cam.move(cam.right()*(elapsed));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			cam.move(cam.forward()*(elapsed));
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			cam.move(cam.backward()*(elapsed));

		

		k.update(elapsed);

		if(frameTime.getElapsedTime().asSeconds() >= 1) {
			frameTime.restart();
			fpsStr = Util::ToString(fps)+"FPS";
			window.setTitle("ImaKart "+fpsStr);
			
			fps = 0;
		}
		//window.setTitle("ImaKart "+fpsStr+ " "+Util::ToString(cam.getPosition().x)+"X " + Util::ToString(cam.getPosition().y)+"Y "+Util::ToString(cam.getPosition().z)+"Z");
		sf::Mouse::setPosition(sf::Vector2i(WINDOW_WIDTH/2, WINDOW_HEIGHT/2), window);
		// Rendering code goes here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Application code goes here

		
		//light3.setPosition(glm::vec3(sin(elapsed)*9000,cos(elapsed)*9000,0));
		light.setPosition(glm::vec3(128*16+sin(elapsed*3)*128*3,100*16,128*16+cos(elapsed*3)*128*3));
		light2.setPosition(glm::vec3(128*16,100*16+sin(elapsed*5),128*14+cos(elapsed*5)*128*3));
		light4.setPosition(glm::vec3(128*14+sin(elapsed*10)*128*3,100*16,128*16+cos(elapsed*10)*128*3));
		//glm::vec3 l2 = glm::normalize(l);
		//glm::vec3 l(-1,-1,0);
		scene.render();
		/*s2.bind();
		//Graph::Render::shader->sendVector(l.x,l.y,l.z, "lightPos");
		sky.render();
		s.bind();
		//Graph::Render::shader->sendVector(l.x,l.y,l.z, "lightPos");
		mesh.render();
		s3.bind();
		mesh3.render();*/
		/*s2.bind();
		mesh2.render();*/
		
		// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
		window.display();
		fps++;
	}

	return EXIT_SUCCESS;
}
