#ifndef NETWORKMANAGER
#define NETWORKMANAGER

#include <Network/Tcp/TcpListener.hpp>
#include <Network/Tcp/TcpSocket.hpp>

namespace Network {

	class Manager {
		public:
			static TcpBase* startServer(int port, SocketProtocol protocol = IPV4) 
			{
				return new TcpBase(NetAddress(port, protocol));
			}
			static TcpSocket* connect(const std::string& ip, int port, SocketProtocol protocol = IPV4)
			{
				return new TcpSocket(NetAddress(ip, port, protocol));
			}
	};
}

#endif