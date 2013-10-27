#include <Graphics/Shader.hpp>
#include <Graphics/Render.hpp>
#include <Utility/LogManager.hpp>
#include <exception>
#include <iostream>
#include <fstream>

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
				Util::LogManager::error("Unknown ShaderType");
				return false;
			}
		return true;
		} catch(const std::exception& e) {
			Util::LogManager::error(e.what());
			return false;
		}

		
	}

	bool Shader::compile()
	{
		m_program = glCreateProgram();
		glCompileShader(m_vertex);
		GLint status;
		glGetShaderiv(m_vertex, GL_COMPILE_STATUS, &status);
		if(status != GL_TRUE)
		{
			GLint length;
			glGetShaderiv(m_vertex, GL_INFO_LOG_LENGTH, &length);
			char* log = new char[length];
			glGetShaderInfoLog(m_vertex, length, 0, log);
			std::string logString(log);
			delete [] log;
			Util::LogManager::error("Error while compiling vertex shader: "+logString);
			return false;
		} else
			m_vertexLoaded = true;

		glCompileShader(m_fragment);
		glGetShaderiv(m_fragment, GL_COMPILE_STATUS, &status);
		if(status != GL_TRUE)
		{
			GLint length;
			glGetShaderiv(m_fragment, GL_INFO_LOG_LENGTH, &length);
			char* log = new char[length];
			glGetShaderInfoLog(m_fragment, length, 0, log);
			std::string logString(log);
			delete [] log;
			Util::LogManager::error("Error while compiling vertex shader: "+logString);
			return false;
		} else
			m_fragmentLoaded = true;
		glAttachShader(m_program, m_vertex);
		glAttachShader(m_program, m_fragment);
		glLinkProgram(m_program);

		glGetProgramiv(m_program, GL_LINK_STATUS, &status);
		if(status != GL_TRUE)
		{
			Util::LogManager::error("Error while linking shader");
			return false;
		} else
			m_programLoaded = true;

		return true;
	}

	GLuint Shader::getProgram() const
	{
		return m_program;
	}

	void Shader::sendVector(float x, float y, float z, const std::string& to) {
		GLint loc = glGetUniformLocation(m_program, to.c_str());
		if(loc != -1) {
			glUniform3f(loc, x,y,z);
		}
	}

	void Shader::bind()
	{
		if(!m_programLoaded)
			Util::LogManager::error("Shader not compiled!");
		else {
			glUseProgram(m_program);
			Render::setShader(this);
		}
	}
	void Shader::unbind()
	{
		glUseProgram(0);
	}


}