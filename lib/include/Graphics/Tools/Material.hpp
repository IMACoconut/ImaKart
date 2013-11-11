#pragma once 

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <string>

namespace Graph {
	class Material {

	public:
		Material();
		~Material();

		bool loadFromFile(const std::string& name);
		GLint getID() const;

		void bind();
		void unbind();

	private:
		GLint m_texID;
		sf::Image m_image;
	};
}