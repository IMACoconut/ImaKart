#include <Game/IA/PlayerBehavior.hpp>
#include <Game/Kart.hpp>
#include <Game/Logic/GameLogic.hpp>

#include <iostream>

PlayerBehavior::PlayerBehavior(Kart& kart, int playerId) :
	KartBehavior(kart), m_playerId(playerId)
{
	
}

void PlayerBehavior::onUpdate(float elapsed) 
{
	auto& xbox = GameLogic::getInstance().getXboxInput();
	if(xbox.isConnected(0)) {
		auto lsaxis = xbox.getAxis(0, Util::XboxAxis::LStick);
		m_kart.accelerate(lsaxis.y);
		m_kart.turn(lsaxis.x);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		m_kart.accelerate(1.f);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_kart.accelerate(-1.f);
	else
		m_kart.accelerate(0.f);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_kart.turn(-1.f);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_kart.turn(1.f);
	else
		m_kart.turn(0.f);
}