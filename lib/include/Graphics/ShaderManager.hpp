#pragma once

#include <map>
#include <iostream>
#include <string>

namespace Graph {

class Shader;
class Node;
class ShaderManager {
public:
	~ShaderManager();

	Shader* buildShader(Node* n);
	Shader* loadShaderFromFile(const std::string& vert, const std::string& frag);

	static ShaderManager& getInstance() {
		static ShaderManager s;
		return s;
	}
protected:
	enum ShaderDetail {
		Has_Diffuse = 1,
		Has_Ambiant = 2,
		Has_Normal = 4
	};

	ShaderManager() = default;
	ShaderManager(const ShaderManager& other) = default;

	std::map<int64_t, Shader*> m_shaders;
};

}