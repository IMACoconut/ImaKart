#include <Game/Entity.hpp>

Entity::~Entity() {
	for(auto it: m_components)
		delete it.second;
	m_components.clear();
}

void Entity::add(const std::string& name, BaseComponent* c) {
	m_components[name] = c;		
}