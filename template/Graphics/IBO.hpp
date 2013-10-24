#pragma once
/*
namespace Graph {
	class IBO {
		IBO()
		{
			glGenBuffers(1, &m_nGLId);
		}
		IBO(const IBO& other) = delete;

		IBO(IBO&& rvalue): m_nGLId(rvalue.m_nGLId) {
			rvalue.m_nGLId = 0;
		}

		IBO& operator=(const IBO& other) = delete;

		IBO& operator =(IBO&& rvalue) {
			m_nGLId = rvalue.m_nGLId;
			rvalue.m_nGLId = 0;
			return *this;
		}

		virtual ~IBO() {
			glDeleteBuffers(1,&m_nGLId);
		}

	private:
		GLuint m_nGLId;
	};

	VBO() {
	
	
		void bind(GLenum target = GL_ARRAY_BUFFER) const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		}
		void unbind(GLenum target = GL_ARRAY_BUFFER) const
		{
			glBindBuffer(target, 0);
		}

		GLuint getGLId() const { return m_nGLId; } 

	protected:
		GLuint m_nGLId;
}*/