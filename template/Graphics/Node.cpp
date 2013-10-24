#include <Graphics/Node.hpp>

namespace Graph {

Node::Node(Node* parent) :
	position(0,0,0), rotation(0,0,0), scale(1,1,1), parent(parent)
{};

Node::~Node() {
	while(children.size()) {
		delete children.back();
		children.pop_back();
	}
}

void Node::addChild(Node* child)
{
	children.push_back(child);
}

void Node::render() {
	draw();
	for(auto it = children.begin(); it != children.end(); ++it) {
		(*it)->draw();
		(*it)->render();
	}
}

}