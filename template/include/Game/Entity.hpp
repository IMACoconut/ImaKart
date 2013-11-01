#pragma once

#include <Game/BaseComponent.hpp>
#include <Game/Component.hpp>
#include <map>

class Entity {
public:
	Entity() = default;

	~Entity();
	
	void add(const std::string& name, BaseComponent* c);

	template <typename T>
	T get(const std::string& name) {
		
		if(m_components.find(name) != m_components.end())
			return static_cast<Component<T>*>(m_components[name])->getValue();
		throw -1;
	}

	template <typename T>
	void set(const std::string& name, T val) {
		if(m_components.find(name) != m_components.end())
			static_cast<Component<T>*>(m_components[name])->setValue(val);
		else
			throw -1;
	}

private:
	std::map<std::string, BaseComponent*> m_components;
};