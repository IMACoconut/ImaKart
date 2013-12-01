#include <Graphics/Tools/Material.hpp>
#include <Utility/LogManager.hpp>

#include <iostream>

namespace Graph {

Material::Material() : m_texID(-1) 
{
	glGenTextures(1, (GLuint*)&m_texID);
}

Material::~Material() 
{
	glDeleteTextures(1, (GLuint*)&m_texID);
}

bool Material::loadFromFile(const std::string& name)
{
	sf::Image image;
	if(!image.loadFromFile(name)) {
		Util::LogManager::error("Unable to load texture \"" + name+"\"");
		return false;
	}

	//m_image.flipHorizontally();
	//m_image.flipVertically();
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.getSize().x, image.getSize().y, 0, format, GL_UNSIGNED_BYTE, image.getPixelsPtr());

	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

bool Material::create(uint32_t width, uint32_t height, uint32_t bits, GLint format, GLint internalFormat) {
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

GLint Material::getID() const {
	return m_texID;
}

void Material::bind(uint8_t unit) {
	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D, m_texID);
	grab();
	glActiveTexture(GL_TEXTURE0);
}

void Material::unbind(uint8_t unit) {
	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D, 0);
	drop();
	glActiveTexture(GL_TEXTURE0);
}
}