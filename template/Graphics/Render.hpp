#pragma once 

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Graph {
	class Shader;
	class Material;

	class Render {
	public:
		typedef enum {
			ProjectionMatrix,
			ViewMatrix,
			ModelMatrix
		} MatrixType;

		typedef enum {
			TextureChannel_1 = 0,
			TextureChannel_Max = TextureChannel_1 +1
		} TextureChannel;

		static void setShader(Shader* shader);
		static void setMatrix(MatrixType t, const glm::mat4& mat);
		static void setTexture(TextureChannel t, Material* mat);

		static glm::mat4 projMatrix;
		static glm::mat4 viewMatrix;
		static glm::mat4 modelMatrix;
		static Shader* shader;
		static bool shaderChanged;
		static Material* materials[TextureChannel_Max];
	};
}