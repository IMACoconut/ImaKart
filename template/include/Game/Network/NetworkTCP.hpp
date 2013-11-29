#pragma once

#include <Game/Network/NetworkConnexion.hpp>

class NetworkTCP : public NetworkConnexion {
	public:
		NetworkTCP(const NzNetAddress& addr, bool listen);
		~NetworkTCP();


	protected:
		void sendOne();
		void recvOne();

		NzTcpBase* socket;
		bool listen;
};