#include <Graphics/Geometry/GBuffer.hpp>
#include <Graphics/Tools/Material.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>

#include <iostream>

namespace Graph {
GBuffer::GBuffer() :
	m_created(false)
{
	for(int i = 0; i<3; ++i) {
        m_textures[i] = new Material;
        //glActiveTexture(GL_TEXTURE0 +i);
    }
    m_depthTexture = new Material;
}
GBuffer::~GBuffer() {
	clear();
}

void GBuffer::clear() {
	if(!m_created)
		return;

	glDeleteFramebuffers(1, &m_fbo);
    for(int i = 0; i<3; ++i)
        delete m_textures[i];
    delete m_depthTexture;
}

bool GBuffer::create(uint32_t width, uint32_t height) {
	glGenFramebuffers(1, &m_fbo);
    m_created = true;
    m_width = width;
    m_height = height;

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    // Create the gbuffer textures

    for (unsigned int i = 0 ; i < 3 ; i++) {
        m_textures[i]->create(width, height, 32, GL_RGB, GL_RGB32F);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i]->getID(), 0);
    }

    m_depthTexture->create(width, height, 32, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT32F);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->getID(), 0);

    GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, DrawBuffers);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        Util::LogManager::error("FB error, status: 0x%x\n"+Util::ToString(Status));
        return false;
    }

    // restore default FBO
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    return true;
}

void GBuffer::bind(GLuint method)
{
    glBindFramebuffer(method, m_fbo);
    GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, DrawBuffers);
}

void GBuffer::unbind(GLuint method)
{
    glBindFramebuffer(method, 0);
}

void GBuffer::save() 
{
    /*setBufferTarget(GBuffer::GBUFFERTARGET_DIFFUSE);
    unsigned int* pixels = new unsigned int[m_width*m_height*3];
    glReadPixels(0,0,m_width, m_height, GL_RGB, GL_UNSIGNED_INT,  pixels);
    sf::Image im;
    im.create(m_width, m_height);
    for(size_t i = 0; i<m_width; ++i)
        for(size_t j = 0; j<m_height; ++j) {
            im.setPixel(i,j, sf::Color(pixels[i*m_width*3+j*3],pixels[i*m_width*3+j*3+1],pixels[i*m_width*3+j*3+2],1));
        }

    delete[] pixels;
    im.saveToFile("test.png");*/
}

void GBuffer::setBufferTarget(GBufferTarget target)
{
    glReadBuffer(GL_COLOR_ATTACHMENT0 + target);
} 

Material* GBuffer::getTexture(GBufferTarget target) const
{
    return m_textures[target];
}
}