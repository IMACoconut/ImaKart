#pragma once

#include <Utility/Input.hpp>

namespace Util {

	class InputManager {
	public:
		static void handleEvent(const sf::Event& e);

		static KeyboardInput Keyboard;
		static JoystickInput Joystick;
		static MouseInput Mouse;
	};

}