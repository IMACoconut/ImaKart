#include <Graphics/Material.hpp>
#include <Utility/LogManager.hpp>

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
	if(!m_image.loadFromFile(name)) {
		Util::LogManager::error("Unable to load texture \"" + name+"\"");
		return false;
	}

	//m_image.flipHorizontally();
	//m_image.flipVertically();
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_image.getSize().x, m_image.getSize().y, 0, format, GL_UNSIGNED_BYTE, m_image.getPixelsPtr());

	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

GLint Material::getID() const {
	return m_texID;
}

void Material::bind() {
	glBindTexture(GL_TEXTURE_2D, m_texID);
}

void Material::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
}