#include <Graphics/ShaderManager.hpp>
#include <Graphics/Render/Render.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Node.hpp>

#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>

namespace Graph {

ShaderManager::~ShaderManager() {
	for(auto it : m_shaders)
		delete (it).second;
	m_shaders.clear();
}

Shader* ShaderManager::buildShader(Node* n) {
	if(n == nullptr)
		return nullptr;

	std::string frag = "#version 330\n\n";
	auto mat = n->getMaterials();

	int64_t flags = 0;
	if(mat[Render::DiffuseTexture])
		flags |= ShaderDetail::Has_Diffuse;
	if(mat[Render::AmbiantTexture])
		flags |= ShaderDetail::Has_Ambiant;
	if(mat[Render::NormalTexture])
		flags |= ShaderDetail::Has_Normal;

	auto it = m_shaders.find(flags);
	if(it != m_shaders.end())
		return (*it).second;

	frag += "in vec2 vertUV;\n";
	frag += "in vec4 vertColor;\n";
	frag += "out vec4 fragColor;\n";

	if(mat[Render::DiffuseTexture])
		frag += "uniform sampler2D diffuseTex;\n";
	
	//if(mat[Render::AmbiantTexture])
	//	frag += "uniform sampler2D ambiantTex;\n";

	if(mat[Render::NormalTexture])
		frag += "uniform sampler2D normalTex;\n";
	else
		frag += "in vec3 vertNorm;\n";

	frag += "uniform vec3 lightPos;\n";

	frag += "void main() {\n";
	frag += "float colorContrib = 1.f;\n";
	if(mat[Render::NormalTexture]) 
		frag += "colorContrib = texture2D(normalTex, vertUV);\n";
	else
		frag += "colorContrib = dot(normalize(lightPos), normalize(vertNorm));\n";

	frag += "fragColor = colorContrib*vertColor";
	if(mat[Render::DiffuseTexture])
		frag += "*texture2D(diffuseTex, vertUV);\n";
	else
		frag += ";\n";

	frag += "}";

	std::string vert = "#version 330\n";
	vert += "layout(location = 0) in vec3 position;\n";
	vert += "layout(location = 1) in vec3 normal;\n";
	vert += "layout(location = 2) in vec2 uv;\n";
	vert += "layout(location = 3) in vec4 color;\n";
	vert += "uniform mat4 viewMatrix;\n";
	vert += "uniform mat4 projMatrix;\n";
	vert += "uniform mat4 modelMatrix;\n";
	vert += "out vec2 vertUV;\n";
	vert += "out vec4 vertColor;\n";

	if(!mat[Render::NormalTexture])
		vert += "out vec3 vertNorm;\n";

	vert += "void main() {\n";
	vert +=	"gl_Position = projMatrix*viewMatrix*modelMatrix*vec4(position, 1.f);\n";
	if(!mat[Render::NormalTexture])
		vert += "vertNorm = normal;\n";

	vert += "vertColor = color;\n";
	vert += "vertUV = uv;\n";
	vert += "}";
	
	Shader* s = new Shader();
	if(!s->loadFromMemory(vert, frag))
	{
		delete s;
		return nullptr;
	}
	s->compile();

	//std::string newEntry = "build-"+Util::ToString(reinterpret_cast<uint64_t>(n));
	m_shaders[flags] = s;
	Util::LogManager::notice("Built shader "+Util::ToString(flags));
	/*Util::LogManager::notice("Vertex:\n"+vert);
	Util::LogManager::notice("Fragment:\n"+frag);*/
	return s;
}

Shader* ShaderManager::loadShaderFromFile(const std::string& vert, const std::string& frag) {
	Shader* s = new Shader();
	if(!s->loadFromFile(vert, Shader::ShaderType_Vertex) || !s->loadFromFile(frag, Shader::ShaderType_Fragment))
	{
		delete s;
		return nullptr;
	}
	s->compile();
	m_shaders[reinterpret_cast<int64_t>(s)] = s;
	return s;
}

}