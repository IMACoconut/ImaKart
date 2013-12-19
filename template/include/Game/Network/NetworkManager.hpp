#pragma once

#include <Network.hpp>
#include <vector>
#include <thread>

class NetworkConnexion;

class NetworkManager {
	public:
		~NetworkManager();

		static NetworkManager& getInstance();

		void addConnexion(NetworkConnexion* connexion);
		void removeConnexion(NetworkConnexion* connexion);

	protected:
		NetworkManager() = default;
		NetworkManager(const NetworkManager& other) = delete;

	private:
		std::vector<NetworkConnexion*> m_connexions;
};