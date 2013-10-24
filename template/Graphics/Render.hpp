#pragma once 

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Graph {
	class Shader;

	class Render {
	public:
		typedef enum {
			ProjectionMatrix,
			ViewMatrix
		} MatrixType;

		static void setShader(Shader* shader);
		static void setMatrix(MatrixType t, const glm::mat4& mat);

		static glm::mat4 projMatrix;
		static glm::mat4 viewMatrix;
		static Shader* shader;
		static bool shaderChanged;
	};
}