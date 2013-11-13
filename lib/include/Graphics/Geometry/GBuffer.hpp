#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

namespace Graph {

class Material;
class GBuffer {
public:
	enum GBufferTarget {
        GBUFFERTARGET_DIFFUSE,
        GBUFFERTARGET_NORMAL,
        GBUFFERTARGET_DEPTH,
        GBUFFERTARGET_MAX
    };

	GBuffer();
	~GBuffer();

	bool create(uint32_t width, uint32_t height);
	void clear();

	void bind(GLuint method);
	void unbind(GLuint method);

	void save();

	void setBufferTarget(GBufferTarget target);
	Material* getTexture(GBufferTarget target) const;

private:
	bool m_created;
	GLuint m_fbo;
	Material* m_textures[GBUFFERTARGET_MAX];
	Material* m_depthTexture;
	uint32_t m_width, m_height;
};
}