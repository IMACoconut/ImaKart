#include <Game/Network/NetworkTCP.hpp>
#include <iostream>

NetworkTCP::NetworkTCP(const NzNetAddress& addr, bool listen) : 
	NetworkConnexion(addr), listen(listen)
{
	std::cout << "TCP" << std::endl;
	if(listen)
		socket = new NzTcpListener(addr);
	else
		socket = new NzTcpSocket(addr);

	start();
}

NetworkTCP::~NetworkTCP()
{
	delete socket;
	std::cout << "~TCP" << std::endl;
}

void NetworkTCP::sendOne() {
	NzPacket* p;
	{
		std::lock_guard<std::mutex> lock(m_out);
		if(m_outgoing.empty())
			return;
		p = m_outgoing.top();
		m_outgoing.pop();
	}
	socket->Write(p);
	p->drop();

}

void NetworkTCP::recvOne() {
	NzPacket* p = socket->Read();
	if(p != nullptr) {
		std::lock_guard<std::mutex> lock(m_in);
		m_incoming.push(p);
	}
}