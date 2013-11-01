#pragma once
#include <string>

class BaseComponent {
	public:
		BaseComponent() : type(-1)  {}
		BaseComponent(int type) :
			type(type)
		{}

		virtual ~BaseComponent();

		int getType() const {
			return type;
		}

		virtual void update() = 0;

	private:
		int type;
};

#include <Game/BaseComponent.inl>