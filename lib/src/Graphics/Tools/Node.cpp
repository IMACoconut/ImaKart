#include <Graphics/Tools/Node.hpp>
#include <Graphics/Tools/Material.hpp>
#include <Graphics/Tools/Shader.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Graph {

Node::Node(Node* parent) :
	position(0,0,0), rotation(0,0,0), scale(1,1,1), mRotation(glm::mat4(1.0)), parent(parent), 
	shader(nullptr), modelMatrix(),
	modelDirty(true), boxDirty(true), sphereDirty(true), 
	drawBox(false),	drawSphere(false)
{
	for(int i = 0; i<Render::TextureChannel_Max; ++i)
		material[i] = nullptr;

	if(parent)
		setParent(parent);
};

Node::~Node() {
	for(int i = 0; i<Render::TextureChannel_Max; ++i)
		if(material[i] != nullptr)
			material[i]->drop();

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

void Node::setRotationAxe(float angle, glm::vec3 axe){
	mRotation = glm::rotate(glm::mat4(), angle, axe);
}

void Node::move(const glm::vec3 m) {
	position += m;
	for(Node* n: children)
		n->move(m);
}

void Node::rotate(const glm::vec3& r) {
	rotation += r;
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

void Node::update(float elapsed) {
	if(modelDirty)
		updateModelMatrix();

	for(auto it: children)
		it->update(elapsed);
}

void Node::render() {
	//Render::setShader(shader);
	/*Render::setMatrix(Render::ModelMatrix, modelMatrix);*/
	
	for(int i = 0; i< Render::TextureChannel_Max; ++i)
		if(material[i] != nullptr)
			Render::setTexture(static_cast<Render::TextureChannel>(i), material[i]);
	
	draw();
	for(auto it: children) {
		it->render();
	}
}

void Node::setMaterial(int pos, Material* m)
{
	if(material[pos] != nullptr)
		material[pos]->drop();
	
	m->grab();
	material[pos] = m;
}
void Node::updateModelMatrix() {
	glm::mat4 rot, scaleM, trans;

	rot = mRotation * rot;
	rot = glm::rotate(rot, rotation.x, glm::vec3(1,0,0));
	rot = glm::rotate(rot, rotation.y, glm::vec3(0,1,0));
	rot = glm::rotate(rot, rotation.z, glm::vec3(0,0,1));
	scaleM = glm::scale(scaleM, scale);
	trans = glm::translate(trans,position);
	modelMatrix = trans*rot*scaleM;
	modelDirty = false;
	computeBoundingSphere();
	computeBoundingBox();
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

const Phys::BSphere& Node::getBoundingSphere() {
	if(sphereDirty)
		computeBoundingSphere();

	sphereDirty = false;
	return m_bsphere;
}

const Phys::AABB3D& Node::getBoundingBox() {
	if(boxDirty)
		computeBoundingBox();
	boxDirty = false;

	return m_aabb;
}

void Node::enableDrawBoundingBox(bool draw) {
	drawBox = draw;
}

void Node::enableDrawBoundingSphere(bool draw) {
	drawSphere = draw;
}

bool Node::isDrawBoundingBoxEnabled() const {
	return drawBox;
}

bool Node::isDrawBoundingSphereEnabled() const {
	return drawSphere;
}

}
