#include <Graphics/Scene/OrthographicCamera.hpp>
#include <Utility/Input/XboxInput.hpp>
#include <Utility/Input/MouseInput.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cmath>

namespace Graph {

OrthographicCamera::OrthographicCamera(Util::Window& window, Node* target) : 
	Camera(window),
	m_targetNode(target), 
	m_minDist(50.f), 
	m_distance(500.f), 
	m_maxDist(5000.f) 
{

}

OrthographicCamera::~OrthographicCamera() {}


void OrthographicCamera::updateProjectionMatrix()
{
	m_proj = glm::ortho(m_fov, m_width/m_height, m_near, m_far);
	m_projDirty = false;
}

}