#pragma once

#include <vector>
#include <tuple>
#include <string>

namespace Graph {

class Shader;
class Node;
class ShaderManager {
public:
	~ShaderManager();

	Shader* buildShader(Node* n);
	Shader* loadShaderFromFile(const std::string& name, const std::string& vert, const std::string& frag);
	Shader* getShader(const std::string& name) const;

	static ShaderManager& getInstance() {
		static ShaderManager s;
		return s;
	}
protected:
	typedef std::tuple<int64_t, std::string, Shader*> ShaderImpl;
	enum ShaderDetail {
		Has_Diffuse = 1,
		Has_Ambiant = 2,
		Has_Normal = 4
	};

	ShaderManager() = default;
	ShaderManager(const ShaderManager& other) = default;

	std::vector<ShaderImpl> m_shaders;
};

}