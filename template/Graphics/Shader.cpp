#include <Graphics/Shader.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/File.hpp>
#include <exception>
#include <iostream>

namespace Graph {
	Shader::Shader() :
		m_vertex(0), m_fragment(0), m_program(0),
		m_vertexLoaded(false), m_fragmentLoaded(false), m_programLoaded(false)
	{}

	Shader::~Shader()
	{

	}

	bool Shader::loadFromFile(const std::string& src, ShaderType t)
	{
		
		try {
			std::ifstream file(src);
			util::IFile f(file);
			std::string data;
			char c;
			while(!file.eof()) {
				c = file.get();
				data += c;
			}
			const char* s = data.c_str();
			if(t == ShaderType_Vertex) {
				m_vertex = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(m_vertex, 1, &s, 0);
			} else if(t == ShaderType_Fragment) {
				m_fragment = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(m_fragment, 1, &s, 0);
			} else {
				util::LogManager::error("Unknown ShaderType");
				return false;
			}
		return true;
		} catch(const std::exception& e) {
			util::LogManager::error(e.what());
			return false;
		}

		
	}

	bool Shader::compile()
	{
		m_program = glCreateProgram();
		glCompileShader(m_vertex);
		glCompileShader(m_fragment);

		glAttachShader(m_program, m_vertex);
		glAttachShader(m_program, m_fragment);
		glLinkProgram(m_program);

		return true;
	}

	void Shader::bind()
	{
		glUseProgram(m_program);
	}
	void Shader::unbind()
	{
		glUseProgram(0);
	}


}