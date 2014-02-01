#include <Graphics/Tools/ShaderManager.hpp>
#include <Graphics/Render/Render.hpp>
#include <Graphics/Tools/Shader.hpp>
#include <Graphics/Tools/Node.hpp>

#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>

namespace Graph {

ShaderManager::~ShaderManager() {
	for(auto it : m_shaders)
		delete std::get<2>(it);
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

	for(auto it = m_shaders.begin(); it != m_shaders.end(); ++it)
		if(std::get<0>(*it) == flags)
			return std::get<2>(*it);

	frag += "in vec2 vertUV;\n";
	frag += "in vec4 vertColor;\n";
	frag += "in vec3 vertPos;\n";
	frag += "out vec4 fragColor[4];\n";

	if(mat[Render::DiffuseTexture])
		frag += "uniform sampler2D diffuseTex;\n";
	
	//if(mat[Render::AmbiantTexture])
	//	frag += "uniform sampler2D ambiantTex;\n";

	if(mat[Render::NormalTexture])
		frag += "uniform sampler2D normalTex;\n";
	else
		frag += "in vec3 vertNorm;\n";

	frag += "uniform vec3 lightPos;\n";
	frag += "uniform float Near;\n";
	frag += "uniform float Far;\n";

	frag += "uniform float isLight;\n";


	frag += "float LinearizeDepth()\n";
	frag += "{\n";
  	frag += "float n = Near;\n";
  	frag += "float f = Far;\n";
  	frag += "float z = gl_FragCoord.z;\n";
  	frag += "return (2.0 * n) / (f + n - z * (f - n));	\n";
	frag += "}\n";

	frag += "float depth() {\n";
	frag += "return LinearizeDepth();\n";
	frag += "}\n";
	frag += "void main() {\n";
	frag += "vec3 N = ";
	if(mat[Render::NormalTexture]) 
		frag += "texture2D(normalTex, vertUV).xyz;\n";
	else
		frag += "vertNorm;\n";

	frag += "N = normalize(N);\n";


	frag += "fragColor[0] = vec4(vertPos,1.f);\n";

	frag += "fragColor[1] = vertColor";
	if(mat[Render::DiffuseTexture])
		frag += "*vec4(texture2D(diffuseTex, vertUV).xyz, 1.f);\n";
	else
		frag += ";\n";
	frag += "fragColor[2] = vec4(N,1.f);\n";
	frag += "fragColor[3] = vec4(isLight, isLight, isLight, 1.f);\n";
	frag += "gl_FragDepth = depth();\n";

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
	vert += "out vec3 vertPos;\n";

	if(!mat[Render::NormalTexture])
		vert += "out vec3 vertNorm;\n";

	vert += "void main() {\n";
	vert +=	"gl_Position = projMatrix*viewMatrix*modelMatrix*vec4(position, 1.f);\n";
	if(!mat[Render::NormalTexture])
		vert += "vertNorm = (modelMatrix*vec4(normal,1.f)).xyz;\n";

	vert += "vertColor = color;\n";
	vert += "vertUV = uv;\n";
	vert += "vertPos = (modelMatrix*vec4(position,1.f)).xyz;\n";
	vert += "}";
	
	Shader* s = new Shader();
	if(!s->loadFromMemory(vert, frag))
	{
		delete s;
		return nullptr;
	}
	s->compile();

	std::string newEntry = "build-"+Util::ToString(reinterpret_cast<uint64_t>(n));
	m_shaders.push_back(std::make_tuple(flags, newEntry, s));
	Util::LogManager::notice("Built shader "+newEntry);
	/*Util::LogManager::notice("Vertex:\n"+vert);
	Util::LogManager::notice("Fragment:\n"+frag);*/
	return s;
}

Shader* ShaderManager::loadShaderFromFile(const std::string& name, const std::string& vert, const std::string& frag) {
	for(auto it = m_shaders.begin(); it != m_shaders.end(); ++it)
		if(std::get<1>(*it) == name)
		{
			Util::LogManager::warning("A shader with the name "+name+" already exists");
			return nullptr;
		}

	Shader* s = new Shader();
	if(!s->loadFromFile(vert, Shader::ShaderType_Vertex) || !s->loadFromFile(frag, Shader::ShaderType_Fragment))
	{
		delete s;
		return nullptr;
	}
	s->compile();
	m_shaders.push_back(std::make_tuple(reinterpret_cast<int64_t>(s), name, s));
	return s;
}

Shader* ShaderManager::getShader(const std::string& name) const {
	for(auto it : m_shaders) {
		if(std::get<1>(it) == name)
			return std::get<2>(it);
	}

	return nullptr;
}

}