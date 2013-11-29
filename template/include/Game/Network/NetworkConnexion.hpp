#pragma once

#include <Network.hpp>
#include <stack>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>

class NetworkConnexion {
	public:
		NetworkConnexion(const NzNetAddress& addr);
		virtual ~NetworkConnexion();

		void start();
		
		void send(NzPacket* p);
		NzPacket* read();
		bool hasInboundData();


	protected:
		void sendLoop();
		void recvLoop();
		virtual void sendOne() = 0;
		virtual void recvOne() = 0;

		NzNetAddress m_address;
		std::atomic_bool m_running;

		std::stack<NzPacket*> m_incoming;
		std::stack<NzPacket*> m_outgoing;
		std::mutex m_in, m_out;
		std::vector<std::thread> m_threads;
		

	friend class NetworkManager;
};