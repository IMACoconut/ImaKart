#include <Game/States/Game.hpp>
#include <Utility/LogManager.hpp>
#include <Game/States/MainMenu.hpp>
#include <Utility.hpp>



static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;

Game::Game(){

}

Game::~Game(){

}

void Game::Init(GameEngine* game){
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

	
	if(!mesh.loadFromFile("../resources/maps/dummy2/heightmap.png")) {
		std::cerr << "Error" << std::endl;
	}
	
	if(!hmtex.loadFromFile("../resources/maps/dummy2/detail.png")) {
		std::cerr << "Error while loading material" << std::endl;
	}
	mesh.setMaterial(0, &hmtex);
	mesh.setScale(glm::vec3(16,16,16));
	mesh.setShader(celShad);
	
	sky.setShader(skyShader);
	
	
	light.setColor(glm::vec3(0,1,0));
	light.setIntensity(3.f);
	light.setRadius(1000.f);
	light.setPosition(glm::vec3(128*16,100.f*16,128*16));
	light.setShader(lightPoint);

	
	light4.setColor(glm::vec3(0,0,1));
	light4.setIntensity(10.f);
	light4.setRadius(1000.f);
	light4.setPosition(glm::vec3(128*16,100.f*16,128*16));
	light4.setShader(lightPoint);

	
	light2.setColor(glm::vec3(1,0, 0));
	light2.setShader(lightSpot);

	
	light3.setColor(glm::vec3(1,1,1));
	light3.setIntensity(.4f);
	light3.setPosition(glm::vec3(0,-9000,0));
	light3.setShader(lightDirectional);

	
	cam.setAspect(WINDOW_WIDTH, WINDOW_HEIGHT);
	scene.setCamera(&cam);
	scene.setBackground(&sky);
	scene.addMesh(&mesh);
	scene.addLight(&light);
	scene.addLight(&light2);
	scene.addLight(&light3);
	scene.addLight(&light4);

	
	m.loadFromFile("../resources/maps/dummy2/map.xml");
	m.loadIntoScene(celShad, scene);

	
	k.loadIntoScene(scene);

	game->getWindow().setMouseCursorVisible(false);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	Util::LogManager::notice("Running");

	
}

void Game::Pause(){

}

void Game::Resume(){

}

void Game::Initialize(){

}

void Game::Release(){

}

void Game::Cleanup(){

}

void Game::HandleEvents(GameEngine* game){
	int old_x = WINDOW_WIDTH/2;
	int old_y = WINDOW_HEIGHT/2;

	sf::Event e;
	sf::RenderWindow& window = game->getWindow();

	while(window.pollEvent(e)) {
		switch(e.type) {
			
			case sf::Event::Closed:
				game->Quit();
				break;
			case sf::Event::MouseMoved:
				if(e.mouseMove.x < 0.001f && e.mouseMove.y < 0.001f)
					break;
				
				cam.rotate(e.mouseMove.x - old_x,e.mouseMove.y-old_y);

				break;
			case sf::Event::KeyPressed:
				switch(e.key.code) {
					case sf::Keyboard::Key::Escape:
						game->PopState();
						break;
					default:
						break;
				}
				break;
			default:
				break;

		}
	}
	

	
}

void Game::Update(GameEngine* game){
	float elapsed = clock.getElapsedTime().asMilliseconds() * 0.0005f;
	
	std::string fpsStr = "0 FPS";

	k.update(elapsed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		cam.move(cam.left()*(elapsed));
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		cam.move(cam.right()*(elapsed));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		cam.move(cam.forward()*(elapsed));
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		cam.move(cam.backward()*(elapsed));

	if(frameTime.getElapsedTime().asSeconds() >= 1) {
		frameTime.restart();
		fpsStr = Util::ToString(fps)+"FPS";
		game->getWindow().setTitle("ImaKart "+fpsStr);
		
		fps = 0;
	}

	sf::Mouse::setPosition(sf::Vector2i(WINDOW_WIDTH/2, WINDOW_HEIGHT/2), game->getWindow());
		
	light3.setPosition(glm::vec3(sin(elapsed*.5f)*9000,cos(elapsed*.5f)*9000,0));
	light.setPosition(glm::vec3(128*16+sin(elapsed*3)*128*3,100*16,128*16+cos(elapsed*3)*128*3));
	light2.setPosition(glm::vec3(128*16,100*16+sin(elapsed*5),128*14+cos(elapsed*5)*128*3));
	light4.setPosition(glm::vec3(128*14+sin(elapsed*10)*128*3,100*16,128*16+cos(elapsed*10)*128*3));

	
}

void Game::Draw(GameEngine* game){
	sf::RenderWindow& window = game->getWindow();
	window.clear();
	scene.render();
	window.display();
	fps++;
}