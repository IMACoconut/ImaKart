#include <Utility/Window.hpp>

namespace Util {
	
	Window::Window(const sf::VideoMode& mode, const std::string& str) :
		sf::RenderWindow(mode, str),
		m_gui(*this), m_mouse(*this)
	{}

	bool Window::pollEvent(sf::Event& e) {
		bool ev = sf::RenderWindow::pollEvent(e);
		m_gui.handleEvent(e);
		m_mouse.handleEvent(e);
		m_xbox.handleEvent(e);
		return ev;
	}

	void Window::display() {
		resetGLStates();
		//m_gui.draw();
		sf::RenderWindow::display();
		m_xbox.begin();
		m_mouse.begin();
	}

	tgui::Gui& Window::getGui() {
		return m_gui;
	}

	XboxInput& Window::getXbox() {
		return m_xbox;
	}

	MouseInput& Window::getMouse() {
		return m_mouse;
	}

}