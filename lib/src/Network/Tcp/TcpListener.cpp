#include <Network/Tcp/TcpListener.hpp>
#include <Utility.hpp>

NzTcpListener::NzTcpListener(const NzNetAddress& address, bool fixedBuffer):
    NzTcpBase(address, fixedBuffer), m_maxClients(5)
{
	sin = m_address.GetSin();
	protocol = m_address.GetProtocol();
	#if defined(USE_WINDOWS)
		int res = WSAEventSelect(m_sock, m_eventsHandler, FD_ACCEPT | FD_CLOSE);
    #endif
    Start();
}

void NzTcpListener::Start()
{
	int err = bind(m_sock, (SOCKADDR *)&sin, sizeof(sin));
	if(err == SOCKET_ERROR)
    {
    	#if defined(USE_WINDOWS)
	        Util::LogManager::error("Erreur lors du bind de la socket. Errno:"+Util::ToString(WSAGetLastError()));
    	#elif defined(USE_LINUX)
			Util::LogManager::error("Erreur lors du bind de la socket. Errno:"+Util::ToString(errno));
    	#endif

        return;
    }

    err = listen(m_sock, m_maxClients);
	if(err == SOCKET_ERROR)
	{
		Util::LogManager::error("Erreur lors de la tentative d'écoute de la socket");
		return;
	}
}

NzTcpSocket* NzTcpListener::WaitForClient()
{
    // Wait 50 msec for a client to connect.
    /*int i = 0;
    if((i = WSAWaitForMultipleEvents(1, &m_eventsHandler, FALSE, 50, FALSE)) == WSA_WAIT_TIMEOUT)
    {
        //std::cout << "no event" << std::endl;
        return nullptr;
    }
    WSAEnumNetworkEvents(m_sock, m_eventsHandler,)*/
    //std::cout << "client connected " << i << " "<< WSA_WAIT_TIMEOUT << " err " << WSAGetLastError() << std::endl;

    // A client has connected, we accept it

    SOCKET csock = INVALID_SOCKET;
	nzSocketAddr addr;
	NzNetAddress net;
	if(protocol == nzSocketProtocol_IPV4) {
		SOCKADDR_IN csin;
		int sinsize = sizeof(csin);
		csock = accept(m_sock, (SOCKADDR *)&csin, reinterpret_cast<socklen_t*>(&sinsize));
		addr.ipv4 = csin;
		net = NzNetAddress(addr, nzSocketProtocol_IPV4);
	}
	else if(protocol == nzSocketProtocol_IPV6) {
		SOCKADDR_IN6 csin;
		int sinsize = sizeof(csin);
		csock = accept(m_sock, (SOCKADDR *)&csin, reinterpret_cast<socklen_t*>(&sinsize));
		addr.ipv6 = csin;
		net = NzNetAddress(addr, nzSocketProtocol_IPV6);
	}
	if(csock == INVALID_SOCKET)
	{
	    if(!m_nonBlocking)
            Util::LogManager::error("Invalid socket accepted");

		return nullptr;
	}
    return new NzTcpSocket(net, csock, m_fixedBuffer);
}