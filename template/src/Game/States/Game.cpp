#include <Game/States/Game.hpp>

#include <Utility/LogManager.hpp>
#include <Game/States/MainMenu.hpp>
#include <Utility.hpp>
#include <Graphics/Scene/FPSCamera.hpp>
#include <Graphics/Scene/OrbitCamera.hpp>

#include <Game/IA/PlayerBehavior.hpp>
#include <Game/Logic/GameLogic.hpp>

Game::Game() :
	k(0), m_loader(*this)
{
	Graph::ShaderManager::getInstance().loadShaderFromFile(
		"skyBox", "../resources/shaders/skybox.vert", "../resources/shaders/skybox.frag");
	Graph::ShaderManager::getInstance().loadShaderFromFile(
		"celShad", "../resources/shaders/textured.vert", "../resources/shaders/textured.frag");

	Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightPoint", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightPoint.frag");
	Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightDirectional", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightDirectional.frag");
	Graph::ShaderManager::getInstance().loadShaderFromFile(
		"DFlightSpot", "../resources/shaders/DFbase.vert", "../resources/shaders/DFlightSpot.frag");
}

Game::~Game(){
	delete cam;
}

void Game::Init(GameEngine* game) {
	m_game = game;
	load();
	//game->PushState(m_loader);
}

void Game::load(){
	Graph::Shader* skyShader = Graph::ShaderManager::getInstance().getShader("skyBox");
	Graph::Shader* celShad = Graph::ShaderManager::getInstance().getShader("celShad");
	Graph::Shader* lightPoint = Graph::ShaderManager::getInstance().getShader("DFlightPoint");
	Graph::Shader* lightDirectional = Graph::ShaderManager::getInstance().getShader("DFlightDirectional");
	Graph::Shader* lightSpot = Graph::ShaderManager::getInstance().getShader("DFlightSpot");
	glClearColor(0,0,0,0);
	
	
	/*if(!mesh.loadFromFile("../resources/maps/dummy2/heightmap.png")) {
		std::cerr << "Error" << std::endl;
	}
	
	if(!hmtex.loadFromFile("../resources/maps/dummy2/detail.png")) {
		std::cerr << "Error while loading material" << std::endl;
	}
	mesh.setMaterial(0, &hmtex);
	mesh.setScale(glm::vec3(16,16,16));*/
	mesh2.loadFromFile("../resources/models/cube.3DS");
	mesh2.setScale(glm::vec3(100,100,100));
	mesh2.setPosition(glm::vec3(128*16,128*16,128*16));
	
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
	
	scene.setBackground(&sky);
	scene.addMesh(&mesh2);
	scene.addLight(&light3);

	
	if(!m.loadFromFile("../resources/maps/dummy2/map.xml"))
		throw -1;

	if(!m.loadIntoScene(scene))
		throw -1;
	k.loadIntoScene(scene);
	k.setBehavior(new PlayerBehavior(k,0));

	cam = new Graph::OrbitCamera(m_game->getWindow(), nullptr);//glm::vec3(0,0,0), glm::vec3(10,10,10), 10.f, 5.f);
	cam->setAspect(m_game->getWindow().getSize().x, m_game->getWindow().getSize().y);
	GameLogic::getInstance().setCamera(cam);
	scene.setCamera(cam);
	

	m_game->getWindow().setMouseCursorVisible(false);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	Util::LogManager::notice("Running");
}

void Game::Pause(GameEngine* game){

}

void Game::Resume(GameEngine* game){
	game->getWindow().setMouseCursorVisible(false);
}

void Game::Initialize(GameEngine* game){

}

void Game::Release(GameEngine* game){

}

void Game::Cleanup(GameEngine* game){

}

void Game::HandleEvents(GameEngine* game){
	sf::Event e;
	auto& window = game->getWindow();
	
	while(window.pollEvent(e)) {
		switch(e.type) {
			
			case sf::Event::Closed:
				game->Quit();
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
	float elapsed = clock.getElapsedTime().asMilliseconds() * 0.05f;
	
	std::string fpsStr = "0 FPS";

	//k.update(elapsed);
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		cam->move(cam->left()*(elapsed));
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		cam->move(cam->right()*(elapsed));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		cam->move(cam->forward()*(elapsed));
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		cam->move(cam->backward()*(elapsed));*/

	
	float time = timeOfDay.getElapsedTime().asMilliseconds() * 0.0001f;
	game->getWindow().getMouse().setPosition(sf::Vector2i(game->getWindow().getSize().x/2, game->getWindow().getSize().y/2));
		
	//light3.setPosition(glm::vec3(sin(time)*9000,cos(time)*9000,0));
	light.setPosition(glm::vec3(128*16+sin(elapsed*3)*128*3,100*16,128*16+cos(elapsed*3)*128*3));
	light2.setPosition(glm::vec3(128*16,100*16+sin(elapsed*5),128*14+cos(elapsed*5)*128*3));
	light4.setPosition(glm::vec3(128*14+sin(elapsed*10)*128*3,100*16,128*16+cos(elapsed*10)*128*3));

	k.update(elapsed);
	scene.update(elapsed);
	clock.restart();
	if(frameTime.getElapsedTime().asSeconds() >= 1) {
		frameTime.restart();
		fpsStr = Util::ToString(fps)+"FPS";
		game->getWindow().setTitle("ImaKart "+fpsStr);
		
		fps = 0;
	}
}

void Game::Draw(GameEngine* game){
	auto& window = game->getWindow();
	window.clear();

	scene.render();
	window.display();
	fps++;
}