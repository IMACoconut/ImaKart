#pragma once

namespace Graph {

class VBO {
	public:
		VBO() {
			glGenBuffers(1, &m_nGLId);
		}
	
		VBO(const VBO& other) = delete;

		VBO(VBO&& rvalue): m_nGLId(rvalue.m_nGLId) {
			rvalue.m_nGLId = 0;
		}

		VBO& operator=(const VBO& other) = delete;

		VBO& operator =(VBO&& rvalue) {
			m_nGLId = rvalue.m_nGLId;
			rvalue.m_nGLId = 0;
			return *this;
		}

		virtual ~VBO() {
			glDeleteBuffers(1,&m_nGLId);
		}

		void bind(GLenum target = GL_ARRAY_BUFFER) const
		{
			glBindBuffer(target, m_nGLId);
		}
		void unbind(GLenum target = GL_ARRAY_BUFFER) const
		{
			glBindBuffer(target, 0);
		}

		GLuint getGLId() const { return m_nGLId; } 

	protected:
		GLuint m_nGLId;
};
}
