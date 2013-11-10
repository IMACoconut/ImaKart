#pragma once

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

namespace Graph {

	class Shader {
		public:
			typedef enum {
				ShaderType_Vertex,
				ShaderType_Fragment
			} ShaderType;

			typedef enum {
				Uniform_Matrix4f,
				Uniform_Vector3f
			} UniformType;

			Shader();
			~Shader();
			Shader(const Shader& other) = delete;

			bool loadFromFile(const std::string& src, ShaderType t);
			bool compile();

			void bind();
			void unbind();

			template <typename T> void send(UniformType t, const std::string& to, const T& val) {
				GLint loc = glGetUniformLocation(m_program, to.c_str());
				if(loc != -1) {
					switch(t) {
						case Uniform_Matrix4f:
							glUniformMatrix4fv(loc, 1,  GL_FALSE, val);
							break;
						case Uniform_Vector3f:
							glUniform3fv(loc, 1, val);
							break;
						default:
							break;
					}
				}
			}

			GLuint getProgram() const;

		private:
			GLuint m_vertex, m_fragment, m_program;
			bool m_vertexLoaded, m_fragmentLoaded, m_programLoaded;
	};
}