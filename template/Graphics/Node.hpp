#pragma once

#include <SFML/Graphics.hpp>

namespace Graph {
	class Node {
	public:
		Node(Node* parent = nullptr);
		Node(const Node& other) = delete;
		virtual ~Node();

		void addChild(Node* child);
		void removeChild(Node* child);

		void setPosition(const sf::Vector3f& position);
		sf::Vector3f getPosition() const;

		void setRotation(const sf::Vector3f& rotation);
		sf::Vector3f getRotation() const;

		void setScale(const sf::Vector3f& scale);
		sf::Vector3f getScale() const;

		void render();

		virtual void draw() = 0;

	protected:
		sf::Vector3f position, rotation, scale;
		Node* parent;
		std::vector<Node*> children;
	};
}