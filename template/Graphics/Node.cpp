#include <Graphics/Node.hpp>
#include <Graphics/Render.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Graph {

Node::Node(Node* parent) :
	position(0,0,0), rotation(0,0,0), scale(1,1,1), parent(parent), 
	modelMatrix(), modelDirty(true)
{
	
};

Node::~Node() {
	while(children.size()) {
		delete children.back();
		children.pop_back();
	}
}

void Node::setScale(const glm::vec3& s) {
	scale = s;
	modelDirty = true;
}

void Node::setRotation(const glm::vec3& r) {
	rotation = r;
	modelDirty = true;
}

void Node::addChild(Node* child)
{
	children.push_back(child);
}

void Node::render() {
	if(modelDirty)
		updateModelMatrix();

	Render::setMatrix(Render::ModelMatrix, modelMatrix);
	draw();
	for(auto it = children.begin(); it != children.end(); ++it) {
		(*it)->render();
	}
}

void Node::updateModelMatrix() {
	glm::mat4 rot, scaleM, trans;
	rot = glm::rotate(rot, rotation.x, glm::vec3(1,0,0));
	rot = glm::rotate(rot, rotation.y, glm::vec3(0,1,0));
	rot = glm::rotate(rot, rotation.z, glm::vec3(0,0,1));
	scaleM = glm::scale(scaleM, scale);
	trans = glm::translate(trans,position);
	modelMatrix = rot*scaleM*trans;
	modelDirty = false;
}

}