#pragma once

#include <Utility/Input/Input.hpp>
#include <SFML/Graphics.hpp>

namespace Util {
class MouseInput : public Input {
public:
	MouseInput(sf::RenderWindow& window);
	void begin();
	void handleEvent(const sf::Event& e);

	sf::Vector2i getMouseDelta() const;
	float getWheelDelta() const;
	bool isPressed(sf::Mouse::Button) const;
	void setPosition(const sf::Vector2i& pos);

private:
	struct MouseState {
		sf::Vector2i mousePos;
		sf::Vector2i mouseDelta;
		float wheelDelta;
	};
	sf::RenderWindow& window;
	MouseState state;
};
}