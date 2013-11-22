#include <Graphics.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>

#include <SFML/Graphics.hpp>
#include <tinyxml2/tinyxml2.h>

#include <Game/Entity.hpp>
#include <Game/Component.hpp>

#include <Game/kart.hpp>
#include <Game/alteration.hpp>
#include <Game/VectorAlt.hpp>

#include <unistd.h>

#include <iostream>
#include <vector>

static const unsigned int FPS = 30;


int main(void) {

	Game::Kart kart;
	std::vector<std::string> affectedVariable;
	affectedVariable.push_back("maniability");
	affectedVariable.push_back("weight");

	std::vector<float> factor;
	factor.push_back(5);
	factor.push_back(9);

	Game::FactorAlteration alt = Game::FactorAlteration("yo", affectedVariable, factor, 5);

	std::cout<<"maniability : "<<kart.get<float>("maniability")<<" weight : "<< kart.get<float>("weight")<<" alteration : "<<(kart.get<Game::VectorAlt>("alterations")).size()<<std::endl;

	kart.update();

	std::cout<<"maniability : "<<kart.get<float>("maniability")<<" weight : "<< kart.get<float>("weight")<<" alteration : "<<(kart.get<Game::VectorAlt>("alterations")).size()<<std::endl;

	kart.addAlteration(&alt);

	std::cout<<"maniability : "<<kart.get<float>("maniability")<<" weight : "<< kart.get<float>("weight")<<" alteration : "<<(kart.get<Game::VectorAlt>("alterations")).size()<<std::endl;

	for (int i = 0; i < 8; ++i)
	{
		kart.update();

		std::cout<<"maniability : "<<kart.get<float>("maniability")<<" weight : "<< kart.get<float>("weight")<<" alteration : "<<(kart.get<Game::VectorAlt>("alterations")).size()<<std::endl;
	}


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
	glClearColor(0.2,0.2,0.2,0);

	Graph::Heightmap mesh;
	if(!mesh.loadFromFile("../resources/maps/dummy2/heightmap.png")) {
		std::cerr << "Error" << std::endl;
	}
	Graph::Material hmtex;
	if(!hmtex.loadFromFile("../resources/maps/dummy2/detail.png")) {
		std::cerr << "Error while loading material" << std::endl;
	}
	mesh.setMaterial(0, &hmtex);
	mesh.setScale(glm::vec3(16,16,16));
	mesh.setShader(celShad);
	Graph::Mesh mesh3;
	if(!mesh3.loadFromFile("../resources/models/cube.3DS"))
		std::cerr << "error while loading cube.3DS" << std::endl;
	mesh3.setScale(glm::vec3(100,100,100));
	
	Graph::Skydome sky;
	sky.setShader(skyShader);
	
	Graph::Light light;
	light.setPosition(glm::vec3(sin(0)*9000,cos(1)*9000,0));
	//s.bind();*/
	Graph::Scene scene;
	Graph::Camera cam;
	cam.setAspect(WINDOW_WIDTH, WINDOW_HEIGHT);
	scene.setCamera(&cam);
	scene.addMesh(&sky);
	scene.addMesh(&mesh);
	scene.addMesh(&mesh3);
	scene.addLight(&light);

	int old_x = WINDOW_WIDTH/2;
	int old_y = WINDOW_HEIGHT/2;

	window.setMouseCursorVisible(false);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	Util::LogManager::notice("Running");

	sf::Clock frameTime, clock;
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			cam.move(cam.left());
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			cam.move(cam.right());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			cam.move(cam.forward());
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			cam.move(cam.backward());

		if(frameTime.getElapsedTime().asSeconds() >= 1) {
			frameTime.restart();
			window.setTitle("ImaKart "+Util::ToString(fps)+"FPS");
			fps = 0;
		}

		sf::Mouse::setPosition(sf::Vector2i(WINDOW_WIDTH/2, WINDOW_HEIGHT/2), window);
		// Rendering code goes here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Application code goes here

		auto elapsed = clock.getElapsedTime().asMilliseconds() * 0.0005f;
		light.setPosition(glm::vec3(sin(elapsed)*9000,cos(elapsed)*9000,0));
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
