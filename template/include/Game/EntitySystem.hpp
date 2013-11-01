#pragma once

#include <vector>

class Entity;

class EntitySystem {
public:
	EntitySystem() = default;
	void registerForUpdate(Entity* e);

	virtual void update() = 0;
private:
	std::vector<Entity*> m_entities;
};

class EntitySystemManager {
public:
	EntitySystemManager() = default;
	void update();
	void registerEntitySystem(EntitySystem* system);

private:
	std::vector<EntitySystem*> m_systems;
};