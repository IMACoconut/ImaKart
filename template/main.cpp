#include <Core/Vector3.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/VAO.hpp>
#include <Graphics/VBO.hpp>
#include <SFML/Graphics.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

static const unsigned int FPS = 30;

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;

struct Vertex2DRGB {
	GLfloat x, y;
	GLfloat r, g, b;

	Vertex2DRGB(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b):
		x(x), y(y), r(r), g(g), b(b) {
	}
};

std::vector<Vertex2DRGB> square() {
	std::vector<Vertex2DRGB> v;

	v.push_back(Vertex2DRGB(-.5,-.5,1,1,1));
	v.push_back(Vertex2DRGB(-.5,.5,1,1,1));
	v.push_back(Vertex2DRGB(.5,.5,1,1,1));

	v.push_back(Vertex2DRGB(-.5,-.5,1,1,1));
	v.push_back(Vertex2DRGB(.5,-.5,1,1,1));
	v.push_back(Vertex2DRGB(.5,.5,1,1,1));
	return v;
}

int main(void) {
	sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL4Imacs");
	window.setFramerateLimit(FPS);

	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
		return EXIT_FAILURE;
	}

	Graph::Shader s;
	s.loadFromFile("resources/shaders/basic.vert", Graph::Shader::ShaderType_Vertex);
	s.loadFromFile("resources/shaders/basic.frag", Graph::Shader::ShaderType_Fragment);
	s.compile();
	glClearColor(0,0,0,0);
	
	Graph::VBO posVBO;
	posVBO.bind();
	auto v = square();
	glBufferData(GL_ARRAY_BUFFER, v.size()*sizeof(Vertex2DRGB), v.data(), GL_STATIC_DRAW);
	posVBO.unbind();

	Graph::VAO vao;
	vao.bind();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	posVBO.bind();
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex2DRGB), (const GLvoid*) (0 * sizeof(GLfloat)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex2DRGB), (const GLvoid*) (2 * sizeof(GLfloat)));
	posVBO.unbind();
	vao.unbind();
	s.bind();

	while(window.isOpen()) {
		// Rendering code goes here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Application code goes here

		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, v.size());
		vao.unbind();

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

		// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
		window.display();
	}

	return EXIT_SUCCESS;
}