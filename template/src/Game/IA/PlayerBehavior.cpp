#include <Game/IA/PlayerBehavior.hpp>
#include <Game/Kart.hpp>
#include <Game/Logic/GameLogic.hpp>

#include <iostream>

PlayerBehavior::PlayerBehavior(Kart& kart, int playerId) :
	KartBehavior(kart), m_playerId(playerId), m_controllerId(-1)
{
	//kart.isPlayer(true);
	
}

void PlayerBehavior::onUpdate(float elapsed) 
{
	if(m_controllerId == -1) {
		for(int i = 0; i<4; ++i)
			if(GameLogic::getInstance().getXboxInput().isConnected(i)) {
				m_controllerId = i;
				break;
			}
	}

	auto& xbox = GameLogic::getInstance().getXboxInput();
/*	if(xbox.isConnected(m_controllerId)) {
		auto lsaxis = xbox.getAxis(m_controllerId, Util::XboxAxis::LStick);

		std::cout << lsaxis.x << " " << lsaxis.y << std::endl;
		if(!Util::eqZero(lsaxis.y))
			m_kart.accelerate(lsaxis.y, elapsed);

		if(!Util::eqZero(lsaxis.x))
			m_kart.turn(lsaxis.x, elapsed);
	}*/
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		m_kart.accelerate(1.f, elapsed);
		//std::cout << "forward" << std::endl;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_kart.accelerate(-1.f, elapsed);
		//std::cout << "backward" << std::endl;
	}
	else {
		m_kart.accelerate(0.f, elapsed);
		//std::cout << "no mvt" << std::endl;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_kart.turn(-1.f, elapsed);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_kart.turn(1.f, elapsed);
	else
		m_kart.turn(0.f, elapsed);
}