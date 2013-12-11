#pragma once

#include <glm/glm.hpp>
#include <Core/Component.hpp>

namespace Core {
	
	class Transform : public Component {
		public:
			Transform(const glm::vec3& position = glm::vec3(), 
				const glm::vec3& rotation = glm::vec3(), 
				const glm::vec3& scale = glm::vec3(), 
				Transform* parent = nullptr);

			void move(const glm::vec3& movement);
			void rotate(float x, float y);
			void lookAt(const glm::vec3& target);
	
			glm::vec3 position, rotation, scale, forward, up, right;
			Transform* parent;
			
			glm::mat4 matrix();

			Transform operator*(Transform& other);
			Transform& operator*=(Transform& other);

			static glm::vec3 Up();
			static glm::vec3 Right();
			static glm::vec3 Forward();

		protected:

	};
}