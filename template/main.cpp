#include <Graphics/Shader.hpp>
#include <Graphics/Scene.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Heightmap.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>
#include <SFML/Graphics.hpp>


#include <iostream>
#include <vector>

static const unsigned int FPS = 30;

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;


int main(void) {
	sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL4Imacs");
	window.setFramerateLimit(FPS);

	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		Util::LogManager::error("Unable to initialize GLEW : "+Util::ToString(glewGetErrorString(glewCode)));
		return EXIT_FAILURE;
	}

	Graph::Shader s;
	s.loadFromFile("resources/shaders/basic.vert", Graph::Shader::ShaderType_Vertex);
	s.loadFromFile("resources/shaders/basic.frag", Graph::Shader::ShaderType_Fragment);
	if(!s.compile()) {
		std::cerr << "Error" << std::endl;
	}
	glClearColor(0,0,0,0);
	
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
	}*/
	
	/*if(!mesh.loadFromFile("resources/models/cube.3DS")) {
		std::cerr << "Error" << std::endl;
	}
	mesh.setScale(glm::vec3(2,10,1));
	mesh.setRotation(glm::vec3(45,45,0));*/
	Graph::Heightmap mesh;
	if(!mesh.loadFromFile("resources/images/heightmap.png")) {
		std::cerr << "Error" << std::endl;
	}
	
	s.bind();
	Graph::Scene scene;
	Graph::Camera cam;
	cam.setAspect(WINDOW_WIDTH, WINDOW_HEIGHT);
	scene.setCamera(&cam);

	int old_x = WINDOW_WIDTH/2;
	int old_y = WINDOW_HEIGHT/2;

	window.setMouseCursorVisible(false);

	Util::LogManager::notice("Running");
	while(window.isOpen()) {
		

		sf::Event e;
		while(window.pollEvent(e)) {
			switch(e.type) {
				
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseMoved:
					cam.rotate(e.mouseMove.x - old_x,old_y-e.mouseMove.y);
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

		sf::Mouse::setPosition(sf::Vector2i(WINDOW_WIDTH/2, WINDOW_HEIGHT/2), window);
		// Rendering code goes here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Application code goes here
		scene.render();
		mesh.render();
		
		// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
		window.display();
	}

	return EXIT_SUCCESS;
}
