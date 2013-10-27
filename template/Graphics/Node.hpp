#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <Graphics/Render.hpp>

namespace Graph {
	class Material;

	class Node {
	public:
		Node(Node* parent = nullptr);
		Node(const Node& other) = delete;
		virtual ~Node();

		void addChild(Node* child);
		void removeChild(Node* child);

		void setPosition(const glm::vec3& position);
		glm::vec3 getPosition() const;

		void setRotation(const glm::vec3& rotation);
		glm::vec3 getRotation() const;

		void setScale(const glm::vec3& scale);
		glm::vec3 getScale() const;

		void render();

		virtual void draw() = 0;
		void setMaterial(int pos, Material* m);

	protected:
		void updateModelMatrix();

		glm::vec3 position, rotation, scale;
		Node* parent;
		std::vector<Node*> children;
		Material* material[Render::TextureChannel_Max];
		glm::mat4 modelMatrix;
		bool modelDirty;
	};
}