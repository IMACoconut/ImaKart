#pragma once

#include <map>
#include <string>

namespace Graph {

class Shader;
class Node;
class ShaderManager {
public:
	~ShaderManager();

	Shader* buildShader(Node* n);
	Shader* loadShaderFromFile(const std::string& name, const std::string& vert, const std::string& frag);

	static ShaderManager& getInstance() {
		static ShaderManager s;
		return s;
	}
private:
	ShaderManager() = default;
	ShaderManager(const ShaderManager& other) = default;

	std::map<std::string, Shader*> m_shaders;
};

}