#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <Utility/Input/MouseInput.hpp>
#include <Utility/Input/XboxInput.hpp>

namespace Util {
	class Window : public sf::RenderWindow {
	public:
		Window(const sf::VideoMode& m, const std::string& title);
		bool pollEvent(sf::Event& e);
		void display();

		tgui::Gui& getGui();
		XboxInput& getXbox();
		MouseInput& getMouse();

	protected:
		tgui::Gui m_gui;
		MouseInput m_mouse;
		XboxInput m_xbox;
	};
}