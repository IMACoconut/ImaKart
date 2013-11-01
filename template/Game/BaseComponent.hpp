#pragma once
#include <string>

class BaseComponent {
	public:
		BaseComponent() : type(-1)  {}
		BaseComponent(int type) :
			type(type)
		{}

		int getType() const {
			return type;
		}

	private:
		int type;
};

#include <Game/BaseComponent.inl>