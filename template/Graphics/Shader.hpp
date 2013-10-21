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

			Shader();
			~Shader();
			Shader(const Shader& other) = delete;

			bool loadFromFile(const std::string& src, ShaderType t);
			bool compile();

			void bind();
			void unbind();

		private:
			GLuint m_vertex, m_fragment, m_program;
			bool m_vertexLoaded, m_fragmentLoaded, m_programLoaded;
	};
}