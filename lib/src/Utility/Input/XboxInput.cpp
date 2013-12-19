#include <Utility/Input/XboxInput.hpp>
#include <iostream>

namespace Util {

XboxInput::XboxInput() {}
XboxInput::~XboxInput() {}

void XboxInput::begin() {}

void XboxInput::handleEvent(const sf::Event& e) {
	switch(e.type) {
		case sf::Event::JoystickButtonPressed:
			{
				XboxButton::Button b = static_cast<XboxButton::Button>(e.joystickButton.button);
				state[e.joystickButton.joystickId].buttons[b] = true;
			}
			break;
		case sf::Event::JoystickButtonReleased:
			{
				XboxButton::Button b = static_cast<XboxButton::Button>(e.joystickButton.button);
				state[e.joystickButton.joystickId].buttons[b] = false;
			}
			break;
		case sf::Event::JoystickMoved:
			{
				XboxAxis::Axis b = getAxis(e.joystickMove);
				if(b != XboxAxis::None) {
					float p = e.joystickMove.position/100.f;
					if(std::fabs(e.joystickMove.position) < 20.f)
						p = 0.f;

					if(e.joystickMove.axis % 2 == 0)
						state[e.joystickMove.joystickId].axis[b].x = p;
					else
						state[e.joystickMove.joystickId].axis[b].y = p;
				} else {
					XboxTrigger::Trigger t = getTrigger(e.joystickMove);
					float p = (e.joystickMove.position+100.f)/200.f;

					if(t != XboxTrigger::None)
						state[e.joystickButton.joystickId].triggers[t] = std::fabs(p);
				}
			}
			break;
		default:
			break;
	}
}

bool XboxInput::isConnected(uint32_t joy) const {
	return sf::Joystick::isConnected(joy);
}

glm::vec2 XboxInput::getAxis(uint32_t joy, XboxAxis::Axis axis) {
	if(!isConnected(joy))
		throw -1;
	return state[joy].axis[axis];
}

float XboxInput::getTrigger(uint32_t joy, XboxTrigger::Trigger trigger) {
	if(!isConnected(joy))
		throw -1;
	return state[joy].triggers[trigger];
}

bool XboxInput::isPressed(uint32_t joy, XboxButton::Button b) {
	if(!isConnected(joy))
		throw -1;
	return state[joy].buttons[b];
}

XboxAxis::Axis XboxInput::getAxis(const sf::Event::JoystickMoveEvent& e) {
	if(static_cast<XboxAnalog::Analog>(e.axis) == XboxAnalog::LStick_X || static_cast<XboxAnalog::Analog>(e.axis) == XboxAnalog::LStick_Y)
		return XboxAxis::LStick;
	else if(static_cast<XboxAnalog::Analog>(e.axis) == XboxAnalog::RStick_X || static_cast<XboxAnalog::Analog>(e.axis) == XboxAnalog::RStick_Y)
		return XboxAxis::RStick;
	else if(static_cast<XboxAnalog::Analog>(e.axis) == XboxAnalog::Dpad_X || static_cast<XboxAnalog::Analog>(e.axis) == XboxAnalog::Dpad_Y)
		return XboxAxis::DPad;
	return XboxAxis::None;
}

XboxTrigger::Trigger XboxInput::getTrigger(const sf::Event::JoystickMoveEvent& e) {
	if(static_cast<XboxAnalog::Analog>(e.axis) == XboxAnalog::LTrig)
		return XboxTrigger::LT;
	else  if(static_cast<XboxAnalog::Analog>(e.axis) == XboxAnalog::RTrig)
		return XboxTrigger::RT;
	return XboxTrigger::None;
}

}