#include <Graphics/Render.hpp>
#include <Graphics/Shader.hpp>
#include <iostream>

namespace Graph {
	glm::mat4 Render::projMatrix = glm::mat4();
	glm::mat4 Render::viewMatrix = glm::mat4();
	Shader* Render::shader = nullptr;
	bool Render::shaderChanged = false;

	void Render::setShader(Shader* s) {
		if(s == shader)
			return;

		shader = s;
		setMatrix(ProjectionMatrix, projMatrix);
		setMatrix(ViewMatrix, viewMatrix);
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
		}

		if(loc != -1) { 
			glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat*)&mat);
		}
	}
}