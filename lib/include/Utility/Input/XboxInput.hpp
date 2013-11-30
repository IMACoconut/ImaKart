#pragma once

#include <Utility/Input/Input.hpp>
#include <map>

namespace Util {
namespace XboxAnalog {
	enum Analog {
		LStick_X = 0,
		LStick_Y = 1,
		LTrig = 2,
		RTrig = 3,
		RStick_X = 4,
		RStick_Y = 5,
		Dpad_X = 6,
		Dpad_Y = 7
	};
	}

	namespace XboxAxis {
	enum Axis {
		LStick = 0,
		RStick = 1,
		DPad = 2,
		Max,
		None
	};
	}
	namespace XboxTrigger {
	enum Trigger{
		LT = 0,
		RT = 1,
		Max,
		None
	};
	}
	namespace XboxButton {
	enum Button {
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LB = 4,
		RB = 5,
		Back = 6,
		Start = 7,
		Home = 8,
		Max
	};
	}

class XboxInput : public Input {
public:
	XboxInput();
	~XboxInput();
	
	void begin();

	void handleEvent(const sf::Event& e);

	bool isConnected(uint32_t joy) const;

	glm::vec2 getAxis(uint32_t joy, XboxAxis::Axis axis);

	float getTrigger(uint32_t joy, XboxTrigger::Trigger trigger);

	bool isPressed(uint32_t joy, XboxButton::Button b);

private:
	struct JoyState{
		glm::vec2 axis[XboxAxis::Max];
		bool buttons[XboxButton::Max];
		float triggers[XboxTrigger::Max];
	};

	XboxAxis::Axis getAxis(const sf::Event::JoystickMoveEvent& e);

	XboxTrigger::Trigger getTrigger(const sf::Event::JoystickMoveEvent& e);

	std::map<uint32_t,JoyState> state;
};
}