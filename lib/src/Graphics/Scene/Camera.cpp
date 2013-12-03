#include <Graphics/Scene/Camera.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Graph {

Camera::Camera(Util::Window& window, const glm::vec3& pos) :
	Node(),
	m_window(window),
	m_view(), m_proj(),
	m_projDirty(true), m_viewDirty(true),
	m_fov(60),
	m_near(.1f), m_far(10000.f),
	m_width(1), m_height(1),
	m_forward(absoluteForward()), m_left(absoluteLeft()), m_up(absoluteUp()),
	m_rotations(0,0,0), m_target(0,0,0)
{
	setPosition(pos);
	lookAt(pos+m_forward);
}

Camera::~Camera() {
}
	
void Camera::setAspect(float width, float height)
{
	m_width = width;
	m_height = height;
	m_projDirty = true;
}

glm::vec2 Camera::getAspect() const {
	return glm::vec2(m_width, m_height);
}

glm::vec2 Camera::getFrustum() const {
	return glm::vec2(m_near, m_far);
}

void Camera::setFrustum(float near, float far) {
	m_near = near; m_far = far;
	m_projDirty=true;
}


void Camera::update(float elapsed) {
	if(m_projDirty)
		updateProjectionMatrix();
	if(m_viewDirty)
		updateViewMatrix();
	onUpdate(elapsed);
}

void Camera::draw() {
	return;
}

void Camera::lookAt(const glm::vec3& pos) {
	glm::vec3 dir = glm::normalize(pos - position);
	m_target = dir;
	m_viewDirty = true;
}

glm::mat4 Camera::getProjMatrix() const {
	return m_proj;
}

glm::mat4 Camera::getViewMatrix() const {
	return m_view;
}

void Camera::updateProjectionMatrix()
{
	m_proj = glm::perspective(m_fov, m_width/m_height, m_near, m_far);
	m_projDirty = false;
}

void Camera::updateViewMatrix() {
	m_view = glm::lookAt(position, m_target, m_up);
	m_up = -glm::cross(m_left, m_forward);
	m_viewDirty = false;
}

glm::vec3 Camera::forward() {
	return m_forward;
}

glm::vec3 Camera::backward() {
	return -m_forward;
}

glm::vec3 Camera::left() {
	return m_left;
}

glm::vec3 Camera::right() {
	return -m_left;
}

glm::vec3 Camera::up() {
	return m_up;
}

glm::vec3 Camera::down() {
	return -m_up;
}

glm::vec3 Camera::absoluteForward() {
	return glm::vec3(-1,0,0);
}

glm::vec3 Camera::absoluteLeft() {
	return glm::vec3(0,0,1);
}

glm::vec3 Camera::absoluteUp() {
	return glm::vec3(0,1,0);
}



}