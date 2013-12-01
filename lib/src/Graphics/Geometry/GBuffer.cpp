#include <Graphics/Geometry/GBuffer.hpp>
#include <Graphics/Tools/Material.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>

#include <iostream>

namespace Graph {
GBuffer::GBuffer() :
	m_created(false), m_depthTexture(nullptr)
{
	glGenFramebuffers(1, &m_fbo);
}
GBuffer::~GBuffer() {
	clear();
    glDeleteFramebuffers(1, &m_fbo);
}

void GBuffer::init(uint32_t width, uint32_t height) 
{
    clear();
    
    m_width = width;
    m_height = height;
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    m_depthTexture = new Material;
    m_depthTexture->create(width, height, 32, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT32F);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->getID(), 0);
    
    //checkErrors();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void GBuffer::clear() {

    delete m_depthTexture;
    m_depthTexture = nullptr;
    for(auto it = m_materials.begin(); it != m_materials.end(); ++it)
       (*it).second->drop();
   m_materials.clear();
}

void GBuffer::createTexture(GBufferTarget target) 
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    Material* mat = new Material;
    mat->create(m_width, m_height, 32, GL_RGB, GL_RGB32F);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_materials.size(), GL_TEXTURE_2D, mat->getID(), 0);
    
    m_materials[target] = mat;

    checkErrors();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}


void GBuffer::setTexture(GBufferTarget target, Material* mat) 
{
    mat->grab();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_materials.size(), GL_TEXTURE_2D, mat->getID(), 0);
    
    m_materials[target] = mat;

    checkErrors();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}/*
bool GBuffer::create(uint32_t width, uint32_t height) {
	
    m_created = true;
    

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    // Create the gbuffer textures

    for (unsigned int i = 0 ; i < 4 ; i++) {
        m_textures[i]->create(width, height, 32, GL_RGB, GL_RGB32F);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i]->getID(), 0);
    }

    m_depthTexture->create(width, height, 32, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT32F);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->getID(), 0);

    GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
    glDrawBuffers(4, DrawBuffers);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        Util::LogManager::error("FB error, status: 0x%x\n"+Util::ToString(Status));
        return false;
    }

    // restore default FBO
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    return true;
}
*/
void GBuffer::bind(GLuint method, int t)
{
    glBindFramebuffer(method, m_fbo);
    if(t == 0)
        t = m_materials.size();

    GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4 };
    glDrawBuffers(t, DrawBuffers);
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
    int pos = 0;
    for(auto p: m_materials) {
        if(p.first == target)
        {
            glReadBuffer(GL_COLOR_ATTACHMENT0 + pos);
            break;
        }
        pos++;
    }
} 

Material* GBuffer::getTexture(GBufferTarget target)
{
    return m_materials[target];
}

void GBuffer::checkErrors() {
    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    std::string str;
    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        switch(Status) {
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                str = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
                break;
            case GL_FRAMEBUFFER_UNDEFINED:
                str = "GL_FRAMEBUFFER_UNDEFINED";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                str = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                str = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
                break;
            case GL_FRAMEBUFFER_UNSUPPORTED:
                str = "GL_FRAMEBUFFER_UNSUPPORTED";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                str = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
                break;
            default:
                str = "other";
                break;
        }
        Util::LogManager::error("FB error, status: "+str);
    }

}
}