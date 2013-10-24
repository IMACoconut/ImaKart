#include <Graphics/Shader.hpp>
#include <Graphics/Scene.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Mesh.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>
#include <Core/Matrix4.hpp>
#include <SFML/Graphics.hpp>


#include <iostream>
#include <vector>

static const unsigned int FPS = 30;

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;


int main(void) {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL4Imacs");
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
	
	Graph::Mesh mesh;
	Graph::VertexBuffer buff;
	buff.addVertex(Graph::Vertex3D(sf::Vector3f(0,0,0), sf::Vector3f(0,0,0), sf::Vector2f(0,0), sf::Color(255,0,0,255)));
	buff.addVertex(Graph::Vertex3D(sf::Vector3f(1,0,0), sf::Vector3f(0,0,0), sf::Vector2f(0,0), sf::Color(0,255,0,255)));
	buff.addVertex(Graph::Vertex3D(sf::Vector3f(1,1,0), sf::Vector3f(0,0,0), sf::Vector2f(0,0), sf::Color(0,0,255,255)));
	buff.addVertex(Graph::Vertex3D(sf::Vector3f(-1,1,0), sf::Vector3f(0,0,0), sf::Vector2f(0,0), sf::Color(0,0,255,255)));
	buff.addTriangle(sf::Vector3ui(0,1,2));
	buff.addTriangle(sf::Vector3ui(0,2,3));
	if(!mesh.loadFromMemory(buff))
	{
		std::cerr << "Error" << std::endl;
	}
	/*if(!mesh.loadFromFile("resources/models/cube.3DS")) {
		std::cerr << "Error" << std::endl;
	}*/
	
	s.bind();
	Graph::Scene scene;
	Graph::Camera cam;
	cam.setAspect(WINDOW_WIDTH, WINDOW_HEIGHT);
	scene.setCamera(&cam);

	Util::LogManager::notice("Running");
	while(window.isOpen()) {
		

		sf::Event e;
		while(window.pollEvent(e)) {
			switch(e.type) {
				default:
					break;
				case sf::Event::Closed:
					window.close();
					break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			cam.move(sf::Vector3f(-1,0,0));
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			cam.move(sf::Vector3f(1,0,0));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			cam.move(sf::Vector3f(0,1,0));
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			cam.move(sf::Vector3f(0,-1,0));

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
