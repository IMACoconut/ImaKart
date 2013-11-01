#include <Graphics/Shader.hpp>
#include <Graphics/Scene.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Heightmap.hpp>
#include <Graphics/Skydome.hpp>
#include <Graphics/Material.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>

#include <SFML/Graphics.hpp>

#include <Game/Entity.hpp>
#include <Game/Component.hpp>

#include <unistd.h>

#include <iostream>
#include <vector>

static const unsigned int FPS = 30;

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;


int main(void) {
	Util::LogManager::init();
	sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL4Imacs");
	//window.setFramerateLimit(FPS);

	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		Util::LogManager::error("Unable to initialize GLEW : "+Util::ToString(glewGetErrorString(glewCode)));
		return EXIT_FAILURE;
	}

	Graph::Shader s;
	s.loadFromFile("../resources/shaders/textured.vert", Graph::Shader::ShaderType_Vertex);
	s.loadFromFile("../resources/shaders/textured.frag", Graph::Shader::ShaderType_Fragment);
	if(!s.compile()) {
		std::cerr << "Error" << std::endl;
	}
	Graph::Shader s2;
	s2.loadFromFile("../resources/shaders/skybox.vert", Graph::Shader::ShaderType_Vertex);
	s2.loadFromFile("../resources/shaders/skybox.frag", Graph::Shader::ShaderType_Fragment);
	if(!s2.compile()) {
		std::cerr << "Error" << std::endl;
	}
	Graph::Shader s3;
	s3.loadFromFile("../resources/shaders/basic.vert", Graph::Shader::ShaderType_Vertex);
	s3.loadFromFile("../resources/shaders/basic.frag", Graph::Shader::ShaderType_Fragment);
	if(!s3.compile()) {
		std::cerr << "Error" << std::endl;
	}
	glClearColor(0.2,0.2,0.2,0);
	
	//Graph::Mesh mesh;
	/*Graph::VertexBuffer buff;
	buff.addVertex(Graph::Vertex3D(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(255,0,0,255)));
	buff.addVertex(Graph::Vertex3D(glm::vec3(1,0,0), glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(0,255,0,255)));
	buff.addVertex(Graph::Vertex3D(glm::vec3(1,1,0), glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(0,0,255,255)));
	buff.addVertex(Graph::Vertex3D(glm::vec3(-1,1,1), glm::vec3(0,0,0), glm::vec2(0,0), sf::Color(0,0,255,255)));
	buff.addTriangle(sf::Vector3i(0,1,2));
	buff.addTriangle(sf::Vector3i(0,2,3));
	if(!mesh.loadFromMemory(buff))
	{
		std::cerr << "Error" << std::endl;
	}
	*/
	
	/*if(!mesh.loadFromFile("../resources/models/cube.3DS")) {
		std::cerr << "Error" << std::endl;
	}
	mesh.setScale(glm::vec3(2,10,1));
	mesh.setRotation(glm::vec3(45,45,0));*/

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
	mesh.setShader(&s);

	Graph::Skydome sky;
	sky.loadSkyMaterial("../resources/images/sky.png");
	sky.loadGlowMaterial("../resources/images/glow.png");
	sky.setShader(&s2);

	s.bind();
	Graph::Scene scene;
	Graph::Camera cam;
	cam.setAspect(WINDOW_WIDTH, WINDOW_HEIGHT);
	scene.setCamera(&cam);
	/*sky.setParent(&scene);
	mesh.setParent(&scene);*/
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
					cam.rotate(e.mouseMove.x - old_x,e.mouseMove.y-old_y);
					old_x = e.mouseMove.x;
					old_y = e.mouseMove.y;
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
		glm::vec3 l = glm::vec3(sin(elapsed)*9000,cos(elapsed)*9000,0);
		//glm::vec3 l2 = glm::normalize(l);
		//glm::vec3 l(-1,-1,0);
		scene.render();
		s2.bind();
		Graph::Render::shader->sendVector(l.x,l.y,l.z, "lightPos");
		sky.render();
		s.bind();
		Graph::Render::shader->sendVector(l.x,l.y,l.z, "lightPos");
		mesh.render();
		/*s2.bind();
		mesh2.render();*/
		
		// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
		window.display();
		fps++;
	}

	return EXIT_SUCCESS;
}
