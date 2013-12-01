#pragma once

#include <map>
#include <cmath>

#include <SFML/Window/Event.hpp>

#include <Utility/LogManager.hpp>
#include <Utility/Tools.hpp>
#include <glm/glm.hpp>

namespace Util {
	class Input {
	public:
		virtual void begin() = 0;
		virtual void handleEvent(const sf::Event& e) = 0;
	};

}