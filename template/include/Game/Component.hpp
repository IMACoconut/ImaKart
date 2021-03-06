#pragma once 

#include <Game/BaseComponent.hpp>

template <typename T>
class Component: public BaseComponent {
public:
	Component(int type, T val) : 
		BaseComponent(type), value(val) {}

	Component(const Component& other) : BaseComponent(other), value(other.value){

	}

	~Component() {}

	T getValue() const {
		return value;
	}

	void setValue(const T& val) {
		value = val;
	}

	void update() {};

private:
	T value;
};