#include <Utility/Input/MouseInput.hpp>

namespace Util {
	
MouseInput::MouseInput(sf::RenderWindow& win) :
	window(win)
{
	state.mouseDelta = sf::Vector2i(0,0);
	state.wheelDelta = 0.f;
	state.mousePos = sf::Mouse::getPosition(win);
}

void MouseInput::begin() {
	state.mouseDelta.x = 0;
	state.mouseDelta.y = 0;
	state.wheelDelta = 0.f;
}

void MouseInput::handleEvent(const sf::Event& e) {
	switch(e.type) {
		case sf::Event::MouseMoved:
			{
				auto newPos = sf::Vector2i(e.mouseMove.x, e.mouseMove.y);
				state.mouseDelta += newPos - state.mousePos;
				state.mousePos = newPos;
			}
			break;
		case sf::Event::MouseWheelMoved:
			state.wheelDelta += e.mouseWheel.delta;
			break;
		default:
			break;
	}
}

sf::Vector2i MouseInput::getMouseDelta() const {
	return state.mouseDelta;
}

float MouseInput::getWheelDelta() const {
	return state.wheelDelta;
}

bool MouseInput::isPressed(const sf::Mouse::Button b) const {
	return sf::Mouse::isButtonPressed(b);
}

void MouseInput::setPosition(const sf::Vector2i& pos) {
	state.mousePos = pos;
	sf::Mouse::setPosition(pos, window);
}
}