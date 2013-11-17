#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <map>

namespace Graph {

class Material;
class GBuffer {
public:
	enum GBufferTarget {
		GBufferTarget_Position = 0,
        GBufferTarget_Albedo = 1,
        GBufferTarget_Normal = 2,
        GBufferTarget_Depth = 3,
        GBufferTarget_Light = 4
    };

	GBuffer();
	~GBuffer();

	void init(uint32_t width, uint32_t height);

	void createTexture(GBufferTarget target);
	void setTexture(GBufferTarget target, Material* mat);

	void clear();

	void bind(GLuint method, int t = 0);
	void unbind(GLuint method);

	void save();

	void setBufferTarget(GBufferTarget target);
	Material* getTexture(GBufferTarget target);

	void checkErrors();

private:
	bool m_created;
	GLuint m_fbo;
	std::map<GBufferTarget, Material*> m_materials;
	Material* m_depthTexture;
	uint32_t m_width, m_height;
};
}