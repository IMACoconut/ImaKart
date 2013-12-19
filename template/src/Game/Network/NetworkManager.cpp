#include <Game/Network/NetworkManager.hpp>
#include <Game/Network/NetworkConnexion.hpp>


NetworkManager::~NetworkManager() {
	for(auto c: m_connexions) {
		delete c;
	}
	m_connexions.clear();
}

NetworkManager& NetworkManager::getInstance() {
	static NetworkManager m;
	return m;
}

void NetworkManager::addConnexion(NetworkConnexion* connexion) {
	m_connexions.push_back(connexion);
}

void NetworkManager::removeConnexion(NetworkConnexion* connexion) {
	for(auto it = m_connexions.begin(); it != m_connexions.end(); ++it) {
		if(*it == connexion) {
			m_connexions.erase(it);
			return;
		}
	}
}