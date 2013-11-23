#include <GameManager/playstate.hpp>
#include <GameManager/gamemenustate.hpp>
#include <GameManager/menustate.hpp>

#include <GameManager/gameengine.hpp>
#include <iostream>
#include <GL/glew.h>

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;

PlayState::PlayState() {
	skyShader = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"skyBox", "../resources/shaders/skybox.vert", "../resources/shaders/skybox.frag");
	celShad = Graph::ShaderManager::getInstance().loadShaderFromFile(
		"celShad", "../resources/shaders/textured.vert", "../resources/shaders/textured.frag");
	if(!mesh.loadFromFile("../resources/maps/dummy2/heightmap.png")) {
		std::cerr << "Error" << std::endl;
	}
	if(!hmtex.loadFromFile("../resources/maps/dummy2/detail.png")) {
		std::cerr << "Error while loading material" << std::endl;
	}
	mesh.setMaterial(0, &hmtex);
	mesh.setScale(glm::vec3(16,16,16));
	mesh.setShader(celShad);
	if(!mesh3.loadFromFile("../resources/models/cube.3DS"))
		std::cerr << "error while loading cube.3DS" << std::endl;
	mesh3.setScale(glm::vec3(100,100,100));
	
	sky.setShader(skyShader);
	
	light.setPosition(glm::vec3(sin(0)*9000,cos(1)*9000,0));
	//s.bind();*/
	cam.setAspect(WINDOW_WIDTH, WINDOW_HEIGHT);
	scene.setCamera(&cam);
	scene.addMesh(&sky);
	scene.addMesh(&mesh);
	scene.addMesh(&mesh3);
	scene.addLight(&light);
	clock.restart();

}

void PlayState::Init()
{
	

}

void PlayState::Initialize()
{
	

}

void PlayState::Release()
{
	

}

void PlayState::Cleanup()
{
	

}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}

void PlayState::HandleEvents(GameEngine* game)
{
	sf::Event e;
	sf::Window& window = game->getWindow();
	int old_x = WINDOW_WIDTH/2;
	int old_y = WINDOW_HEIGHT/2;
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
							game->PopState();
							break;
						case sf::Keyboard::Key::Space:
							std::cout << "Pausing game" << std::endl;	
							
							game->PushState(GameMenuState::getInstance());


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
}

void PlayState::Update(GameEngine* game) 
{

}

void PlayState::Draw(GameEngine* game) 
{
	// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
	sf::Window& window = game->getWindow();

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
	
}

