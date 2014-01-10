#pragma once

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

namespace Graph {
	class ShaderManager;
	class Shader {
		public:
			typedef enum {
				ShaderType_Vertex,
				ShaderType_Fragment
			} ShaderType;

			typedef enum {
				Uniform_Matrix4f,
				Uniform_Vector3f,
				Uniform_Float,
				Uniform_Integer
			} UniformType;

			Shader();
			~Shader();
			Shader(const Shader& other) = delete;

			bool loadFromFile(const std::string& src, ShaderType t);
			bool loadFromMemory(const std::string& vert, const std::string& frag);
			bool compile();

			void bind();
			void unbind();

			template <typename T> void send(UniformType t, const std::string& to, const T& val) {
				GLint loc = glGetUniformLocation(m_program, to.c_str());
				if(loc != -1) {
					switch(t) {
						case Uniform_Matrix4f:
							glUniformMatrix4fv(loc, 1,  GL_FALSE, reinterpret_cast<const GLfloat*>(val));
							break;
						case Uniform_Vector3f:
							glUniform3fv(loc, 1, reinterpret_cast<const GLfloat*>(val));
							break;
						case Uniform_Float:
							glUniform1f(loc, *reinterpret_cast<const GLfloat*>(val));
							break;
						case Uniform_Integer:
							glUniform1i(loc, *reinterpret_cast<const GLint*>(val));	
						default:
							break;
					}
				}
			}

			GLuint getProgram() const;

		private:
			GLuint m_vertex, m_fragment, m_program;
			bool m_vertexLoaded, m_fragmentLoaded, m_programLoaded;
			std::string m_vertFile, m_fragFile;
	
		friend class ShaderManager;

	};
}