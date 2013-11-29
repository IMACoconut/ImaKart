#include <Utility/InputManager.hpp>

namespace Util {

KeyboardInput InputManager::Keyboard;
JoystickInput InputManager::Joystick;
MouseInput InputManager::Mouse;

void InputManager::handleEvent(const sf::Event& e) {
	Keyboard.handleInput(e);
	Joystick.handleInput(e);
	Mouse.handleInput(e);
}

}