#include <Game/States/Game.hpp>

#include <Utility/LogManager.hpp>
#include <Game/States/MainMenu.hpp>
#include <Utility.hpp>
#include <Graphics/Scene/FPSCamera.hpp>
#include <Graphics/Scene/OrbitCamera.hpp>
#include <Graphics/Scene/KartCamera.hpp>

#include <Game/IA/PlayerBehavior.hpp>
#include <Game/IA/IABehavior.hpp>
#include <Game/Logic/GameLogic.hpp>

Game::Game() :
	m_loader(*this), map(nullptr)
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
	map = GameLogic::getInstance().getMap();
	
	auto& gui = m_game->getWindow().getGui();
	m_clockDisplay = tgui::Label::Ptr(gui);
	m_clockDisplay->setPosition(750,40);
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
	//mesh2.loadFromFile("../resources/models/cube.3DS");
	sky.setShader(skyShader);
	
	
	light.setColor(glm::vec3(0,1,0));
	light.setIntensity(3.f);
	light.setRadius(50.f*16);
	light.setPosition(glm::vec3(128*16,100.f*16,128*16));
	light.setShader(lightPoint);

	
	light4.setColor(glm::vec3(0,0,1));
	light4.setIntensity(3.f);
	light4.setRadius(50.f*16);
	light4.setPosition(glm::vec3(128*16,100.f*15,128*16));
	light4.setShader(lightPoint);

	
	light2.setColor(glm::vec3(1,0, 0));
	light2.setShader(lightSpot);

	
	light3.setColor(glm::vec3(1,1,1));
	light3.setIntensity(.7f);
	light3.setPosition(glm::vec3(0,-9000,0));
	light3.setShader(lightDirectional);
	
	scene.setBackground(&sky);
	scene.addLight(&light3);
	scene.addLight(&light);
	scene.addLight(&light2);
	scene.addLight(&light4);

//////init kart ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int numberOfKarts = 1;
	int numberOfPlayer = 1;
	for (int i = 0; i < numberOfKarts; ++i)
	{
		Kart* tmp = addKart(KartType_3);
		if(i < numberOfPlayer){
			//std::cout << "Player" << std::endl;
			tmp->setBehavior(new PlayerBehavior(*tmp, i));
		}
		else {
			//std::cout << "IA" << std::endl;
			tmp->setBehavior(new IABehavior(*tmp, map->getCheckpoints()));
		}
	}

map->loadIntoScene(scene);
	

//////init camera////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cam =  /*new Graph::KartCamera(m_game->getWindow(), &(karts[0]->mesh));*//*new Graph::OrbitCamera(m_game->getWindow(), &mesh2);*/new Graph::FPSCamera(m_game->getWindow(), glm::vec3(128*16,128*16,128*16), glm::vec3(10,10,10), 10.f, 5.f);
	cam->setAspect(m_game->getWindow().getSize().x, m_game->getWindow().getSize().y);
	GameLogic::getInstance().setCamera(cam);
	scene.setCamera(cam);

	m_game->getWindow().setMouseCursorVisible(false);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	GameLogic::getInstance().startRace();
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

	//cam->onUpdate(elapsed);
	//k.update(elapsed);
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		cam->move(cam->left()*(elapsed));
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		cam->move(cam->right()*(elapsed));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		cam->move(cam->forward()*(elapsed));
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		cam->move(cam->backward()*(elapsed));*/

	
	float time = timeOfDay.getElapsedTime().asSeconds() * 0.1f;
	game->getWindow().getMouse().setPosition(sf::Vector2i(game->getWindow().getSize().x/2, game->getWindow().getSize().y/2));
		
	//light3.setPosition(glm::vec3(sin(time)*9000,cos(time)*9000,0));
	light.setPosition(glm::vec3(128*16+sin(time*3)*128*3,100*16,128*16+cos(time*3)*128*3));
	light2.setPosition(glm::vec3(128*16,100*16+sin(time*5),128*14+cos(time*5)*128*3));
	light4.setPosition(glm::vec3(128*14+sin(time*10)*128*3,100*16,128*16+cos(time*10)*128*3));


	map->update(elapsed);
	scene.update(elapsed);
	clock.restart();
	const Util::Clock& raceTimer = GameLogic::getInstance().getClock();
	std::string sec;
	if(raceTimer.GetSeconds()%60 < 10)
		sec = "0"+ Util::ToString(raceTimer.GetSeconds()%60);
	else
		sec = Util::ToString(raceTimer.GetSeconds()%60);
	std::string msec = "";
	if(raceTimer.GetMilliseconds()%1000 < 100)
		msec += '0';
	if(raceTimer.GetMilliseconds()%1000 < 10)
		msec += '0';
	msec += Util::ToString(raceTimer.GetMilliseconds()%1000);

	m_clockDisplay->setText(Util::ToString(raceTimer.GetMinutes())+":"+sec+":"+msec);
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

Kart* Game::addKart(KartType type){
	Kart* k = new Kart(karts.size());
	switch(type) {
		case KartType_1:
			k->set<std::string>("skin", "");
			k->set<int>("hp", 5);
			k->set<float>("weight", 5);
			k->set<float>("speedMaxForward", 5.f);
			k->set<float>("speedMaxBack", -1.f);
			k->set<float>("acceleration", 0.025f);
			k->set<float>("maniability", 0.35f);
			break;
		case KartType_2:
			k->set<std::string>("skin", "");
			k->set<int>("hp", 8);
			k->set<float>("weight", 8);
			k->set<float>("speedMaxForward", 8.f);
			k->set<float>("speedMaxBack", -2.f);
			k->set<float>("acceleration", 0.01f);
			k->set<float>("maniability", 0.3f);
			break;
		case KartType_3:
			k->set<std::string>("skin", "");
			k->set<int>("hp", 3);
			k->set<float>("weight", 4);
			k->set<float>("speedMaxForward", 4.f);
			k->set<float>("speedMaxBack", -1.f);
			k->set<float>("acceleration", 0.05f);
			k->set<float>("maniability", 0.4f);
			break;
		default:
			break;
	}
	map->addKart(k);
	karts.push_back(k);
	return k;
}