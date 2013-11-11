#include <Graphics/Tools/Node.hpp>
#include <Graphics/Tools/Material.hpp>
#include <Graphics/Tools/Shader.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Graph {

Node::Node(Node* parent) :
	position(0,0,0), rotation(0,0,0), scale(1,1,1), parent(parent), 
	shader(nullptr), modelMatrix(), modelDirty(true)
{
	for(int i = 0; i<Render::TextureChannel_Max; ++i)
		material[i] = nullptr;

	if(parent)
		setParent(parent);
};

Node::~Node() {
	for(Node* c : children)
		c->setParent(nullptr);
	setParent(nullptr);
}

void Node::setPosition(const glm::vec3& p) {
	position = p;
	modelDirty = true;
}

glm::vec3 Node::getPosition() const {
	return position;
}

void Node::setScale(const glm::vec3& s) {
	scale = s;
	modelDirty = true;
}

void Node::setRotation(const glm::vec3& r) {
	rotation = r;
	modelDirty = true;
}

void Node::setParent(Node* p) 
{
	if(p == this || p == parent)
		return;

	if(parent)
		parent->removeChild(this);
	parent = p;

	if(parent)
		parent->addChild(this);
}

void Node::addChild(Node* child)
{
	if(std::find(children.begin(), children.end(), child) == children.end()) // On teste si child n'est pas dans la liste
		children.push_back(child);
}

void Node::removeChild(Node* child)
{
	auto it = std::find(children.begin(), children.end(), child); // On recherche le child dans la liste
	if(it != children.end())
		children.erase(it);
}

void Node::render() {
	if(modelDirty)
		updateModelMatrix();
	
	//Render::setShader(shader);
	/*Render::setMatrix(Render::ModelMatrix, modelMatrix);*/
	
	for(int i = 0; i< Render::TextureChannel_Max; ++i)
		if(material[i] != nullptr)
			Render::setTexture(static_cast<Render::TextureChannel>(i), material[i]);
	
	draw();
	for(auto it = children.begin(); it != children.end(); ++it) {
		(*it)->render();
	}
}

void Node::setMaterial(int pos, Material* m)
{
	material[pos] = m;
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

void Node::setShader(Shader* s)
{
	shader = s;
}

Shader* Node::getShader() const {
	return shader;
}

glm::mat4 Node::getModelMatrix() const {
	return modelMatrix;
}

Material* const* Node::getMaterials() const {
	return material;
}

}