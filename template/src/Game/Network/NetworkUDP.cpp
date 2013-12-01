#include <Game/Network/NetworkUDP.hpp>

NetworkUDP::NetworkUDP(const NzNetAddress& addr, bool listen) : 
	NetworkConnexion(addr) 
{
	std::cout << "UDP" << std::endl;
	if(listen)
		socket = new NzUdpListener(addr);
	else
		socket = new NzUdpSocket(addr);
	
	start();
}

NetworkUDP::~NetworkUDP()
{
	delete socket;
	std::cout << "~UDP" << std::endl;
}

void NetworkUDP::sendOne() {

}

void NetworkUDP::recvOne() {

}