#include <Network/Tcp/TcpSocket.hpp>

NzTcpSocket::NzTcpSocket(const NzNetAddress& address, SOCKET sock, bool fixedBuffer) :
    NzTcpBase(address, sock, fixedBuffer),
    m_connected(true), m_timeout(5)
    { }
NzTcpSocket::NzTcpSocket(const NzNetAddress& remoteAddress, bool fixedBuffer, int32_t timeout, bool nonBlocking) :
    NzTcpBase(remoteAddress, fixedBuffer),
	m_connected(false), m_timeout(timeout)
{
    SetNonBlocking(nonBlocking);
    Start();
}

void NzTcpSocket::Start()
{
	int res;
	int timeout = 0;
	bool b = m_nonBlocking;
	SetNonBlocking(false);
	do {
        //std::cout << "blocking: " << !m_nonBlocking << std::endl;
		res = connect(m_sock, (SOCKADDR *)&m_address.GetSin(), sizeof(m_address.GetSin()));
		//std::cout << WSAGetLastError() << std::endl;std::cout << res << std::endl;
		if(res != -1)
			m_connected = true;
		else {
			pause(1000);
		}
		timeout++;

	} while(res == -1 && timeout < m_timeout);
	SetNonBlocking(b);
}

bool NzTcpSocket::IsConnected()
{
	return m_connected;
}
