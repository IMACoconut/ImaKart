#include <Graphics/Render/Render.hpp>
#include <Graphics/Tools/Shader.hpp>
#include <Graphics/Tools/Material.hpp>
#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>
#include <iostream>

namespace Graph {
	glm::mat4 Render::projMatrix = glm::mat4();
	glm::mat4 Render::viewMatrix = glm::mat4();
	glm::mat4 Render::modelMatrix = glm::mat4();
	Shader* Render::shader = nullptr;
	bool Render::shaderChanged = false;
	Material* Render::materials[TextureChannel_Max];

	void Render::setShader(Shader* s) {
		if(s == shader)
			return;

		shader = s;
		/*setMatrix(ProjectionMatrix, projMatrix);
		setMatrix(ViewMatrix, viewMatrix);
		setMatrix(ModelMatrix, modelMatrix);
		for(int i = TextureChannel_1; i < TextureChannel_Max; ++i)
			setTexture(static_cast<TextureChannel>(i), materials[i]);	*/	
	}


	void Render::setMatrix(MatrixType t, const glm::mat4& mat) {
		if(shader == nullptr)
			return;

		GLuint shaderProgram = shader->getProgram();
		GLint loc = -1;
		switch(t) {
			case ProjectionMatrix:
				loc = glGetUniformLocation(shaderProgram, "projMatrix");
				projMatrix = mat;
				break;
			case ViewMatrix:
				loc = glGetUniformLocation(shaderProgram, "viewMatrix");
				viewMatrix = mat;
				break;
			case ModelMatrix:
				loc = glGetUniformLocation(shaderProgram, "modelMatrix");
				modelMatrix = mat;
				break;
		}

		if(loc != -1) {
			glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat*)&mat);
		}
	}

	void Render::setTexture(TextureChannel t, Material* m) {
		if(materials[t])
		{
			//std::cout << "dropping unit " << static_cast<int>(t) << " " << materials[t]->getID() << " " << materials[t]->getRefCount() << std::endl;
			materials[t]->unbind(static_cast<int>(t));
			materials[t]->drop();
			materials[t] = nullptr;
		}
		
		if(shader == nullptr || m == nullptr)
			return;

		m->grab();
		materials[t] = m;

		GLint loc = -1;
		GLuint shaderProgram = shader->getProgram();
		std::string str = "";

/*
		static const char* strs[] = {
			"diffuseTex", "ambiantTex", "normalTex", "depthTex"
		};
		loc = glGetUniformLocation(shaderProgram, strs[t]);
*/
		switch(t) {
			case DiffuseTexture:
				loc = glGetUniformLocation(shaderProgram, "diffuseTex");
				str = "diffuseTex";
				break;
			case AmbiantTexture:
				loc = glGetUniformLocation(shaderProgram, "ambiantTex");
				str = "ambiantTex";
				break;
			case NormalTexture:
				loc = glGetUniformLocation(shaderProgram, "normalTex");
				str = "normalTex";
				break;
			case DepthTexture:
				loc = glGetUniformLocation(shaderProgram, "depthTex");
				str = "depthTex";
				break;
			default:
				break;
		}
		//std::cout << "binding unit " << static_cast<int>(t) << " " << m->getID() << " " << materials[t]->getRefCount() << " on " << str << std::endl;

		if(loc != -1) {
			m->bind(static_cast<int>(t));
			
			glUniform1i(loc, static_cast<int>(t));
		} else {
			//Util::LogManager::error(str+" not found");
		}
	}

	void Render::unbindTextures() {
		for(int i = 0; i<4; ++i) {
			auto t = materials[static_cast<TextureChannel>(i)];
			if(t)
				t->unbind(i);
		}
	}
}