#include <Graphics/Render/Render.hpp>
#include <Graphics/Tools/Shader.hpp>
#include <Graphics/Tools/Material.hpp>
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

	void Render::setTexture(TextureChannel t, Material* m, uint8_t unit) {
		if(m == nullptr) {
			materials[t]->unbind();
			materials[t] = nullptr;
			return;
		}

		if(materials[t] == m || shader == nullptr)
			return;

		materials[t] = m;
		
		GLint loc = -1;
		GLuint shaderProgram = shader->getProgram();
		switch(t) {
			case DiffuseTexture:
				loc = glGetUniformLocation(shaderProgram, "diffuseTex");
				break;
			case AmbiantTexture:
				loc = glGetUniformLocation(shaderProgram, "ambiantTex");
				break;
			case NormalTexture:
				loc = glGetUniformLocation(shaderProgram, "normalTex");
				break;
			case DepthTexture:
				loc = glGetUniformLocation(shaderProgram, "depthTex");
				break;
			default:
				break;
		}
		if(loc != -1) {
			glActiveTexture(GL_TEXTURE0 + static_cast<int>(t));
			glUniform1i(loc, static_cast<int>(t));
			m->bind(unit);
		}
	}
}