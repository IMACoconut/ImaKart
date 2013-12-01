#pragma once

#include <Game/Network/NetworkConnexion.hpp>

class NetworkUDP : public NetworkConnexion {
	public:
		NetworkUDP(const NzNetAddress& addr, bool listen);
		~NetworkUDP();


	protected:
		void sendOne();
		void recvOne();

	private:
		NzUdpBase* socket;
};