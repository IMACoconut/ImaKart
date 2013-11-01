#include <Game/EntitySystem.hpp>
#include <Game/Entity.hpp>

void EntitySystem::registerForUpdate(Entity* e) {
	m_entities.push_back(e);
}

void EntitySystemManager::update() {
	for(auto es : m_systems)
		es->update();
}

void EntitySystemManager::registerEntitySystem(EntitySystem* system) {
	m_systems.push_back(system);
}