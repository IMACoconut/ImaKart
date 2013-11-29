#pragma once

#include <functional>
#include <map>
#include <vector>
#include <cmath>

#include <SFML/Window/Event.hpp>

#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>

namespace Util {
	class Input {
	public:
		virtual void handleInput(const sf::Event& e) = 0;
	};

	class KeyboardInput : public Input {
	public:
		bool bind(sf::Keyboard::Key k, std::function<void(bool)> f) {
			m_keys[k].push_back(f);
			return true;
		}

		void handleInput(const sf::Event& e) {
			if(e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased)
					for(auto f: m_keys[e.key.code])
						f((e.type == sf::Event::KeyPressed) ? true : false);
		}
	private:
		std::map<sf::Keyboard::Key, std::vector<std::function<void(bool)>>> m_keys;
	};

	class JoystickInput : public Input {
	public:
		bool bindButton(uint32_t joystickId, uint32_t button, std::function<void(bool)> f) {
			if(!sf::Joystick::isConnected(joystickId)) {
				LogManager::warning("Joystick "+ToString(joystickId)+" not connected.");
				return false;
			}
			if(button >= sf::Joystick::getButtonCount(joystickId)) {
				LogManager::warning("Joystick "+ToString(joystickId)+" has not button "+ToString(button));
				return false;
			}
			m_buttons[joystickId][button].push_back(f);
			return true;
		}

		bool bindAxis(uint32_t joystickId, sf::Joystick::Axis axis, std::function<void(float)> f) {
			if(!sf::Joystick::isConnected(joystickId)) {
				LogManager::warning("Joystick "+ToString(joystickId)+" not connected.");
				return false;
			}
			if(!sf::Joystick::hasAxis(joystickId, axis)) {
				LogManager::warning("Joystick "+ToString(joystickId)+" has not axis "+ToString(axis));
				return false;
			}
			m_axis[joystickId][axis].push_back(f);
			return true;
		}

		void handleInput(const sf::Event& e) {
			if(e.type == sf::Event::JoystickButtonPressed || e.type == sf::Event::JoystickButtonReleased) {
				for(auto f : m_buttons[e.joystickButton.joystickId][e.joystickButton.button])
					f((e.type == sf::Event::JoystickButtonPressed) ? true : false);
			} else if(e.type == sf::Event::JoystickMoved) {
				if(std::fabs(e.joystickMove.position) < 5.f)
					return;
				for(auto f : m_axis[e.joystickMove.joystickId][e.joystickMove.axis]) {
					f(e.joystickMove.position/100.f);
				}
			}
		}

	private:
		std::map<uint32_t, std::map<uint32_t, std::vector<std::function<void(bool)>>>> m_buttons;
		std::map<uint32_t, std::map<sf::Joystick::Axis, std::vector<std::function<void(float)>>>> m_axis;
	};

	class MouseInput : public Input {
	public:
		MouseInput() : m_oldX(0), m_oldY(0) {}

		void bindButton(sf::Mouse::Button b, std::function<void(bool)> f){
			m_buttons[b].push_back(f);
		}

		void bindWheel(std::function<void(float)> f) {
			m_wheel.push_back(f);
		}

		void bindMove(std::function<void(int,int,int,int)> f) {
			m_move.push_back(f);
		}

		void setCursorPosition(int x, int y) {
			m_oldX = x;
			m_oldY = y;
		}

		void handleInput(const sf::Event& e) {
			if(e.type == sf::Event::MouseMoved) {
				if(e.mouseMove.x < 0.001 && e.mouseMove.y < 0.001f)
					return;

				for(auto f: m_move)
					f(e.mouseMove.x, e.mouseMove.y, e.mouseMove.x - m_oldX, e.mouseMove.y - m_oldY);
				m_oldX = e.mouseMove.x;
				m_oldY = e.mouseMove.y;
			} else if(e.type == sf::Event::MouseWheelMoved) {
				for(auto f: m_wheel)
					f(e.mouseWheel.delta);
			} else if(e.type == sf::Event::MouseButtonPressed || e.type == sf::Event::MouseButtonReleased)
				for(auto f: m_buttons[e.mouseButton.button])
					f((e.type == sf::Event::MouseButtonPressed) ? true : false);
		}

	private:
		std::map<sf::Mouse::Button, std::vector<std::function<void(bool)>>> m_buttons;
		std::vector<std::function<void(float)>> m_wheel;
		std::vector<std::function<void(int,int,int,int)>> m_move;
		int m_oldX, m_oldY;
	};
}