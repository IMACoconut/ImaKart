#include <Network/Udp/UdpBase.hpp>

NzUdpBase::NzUdpBase() : NzSocket(nzSocketType_UDP)
{
	if(m_address.GetProtocol() == nzSocketProtocol_IPV6)
		m_sock = socket(AF_INET6,SOCK_DGRAM, 0);
	else if(m_address.GetProtocol() == nzSocketProtocol_IPV4)
		m_sock = socket(AF_INET,SOCK_DGRAM, 0);
}

NzUdpBase::NzUdpBase(const NzNetAddress& address) : NzSocket(address, nzSocketType_UDP)
{
	if(m_address.GetProtocol() == nzSocketProtocol_IPV6)
		m_sock = socket(AF_INET6,SOCK_DGRAM, 0);
	else if(m_address.GetProtocol() == nzSocketProtocol_IPV4)
		m_sock = socket(AF_INET,SOCK_DGRAM, 0);
}

NzUdpBase::~NzUdpBase(void)
{
    #if defined(USE_WINDOWS)
	   closesocket(m_sock);
    #elif defined(USE_LINUX)
        close(m_sock);
    #endif
}

NzPacket* NzUdpBase::Read()
{
	/*size_t size = 0;
	SOCKADDR_IN client;
	int len = sizeof(client);
	recvfrom(m_sock, (char*)&size, sizeof(size_t), 0, (sockaddr*)&client, &len);
	char* buffer = new char[size];
	recvfrom(m_sock, buffer, size, 0, (sockaddr*)&client, &len);
	buffer[size] = 0;

	NzPacket* p = new NzPacket(buffer, size);
	nzSocketAddr addr;
	addr.ipv4 = client;
	//p->peer = new NzNetAddress(addr, nzSocketProtocol_IPV4);
	delete buffer;*/
	NzNetAddress addr;
	return ReadFrom(addr);
	//NazaraError("Please use UdpBase::ReadFrom() instead of UdpBase::Read()")
}

void NzUdpBase::Write(NzPacket* packet)
{
        WriteTo(packet, m_address);
}

void NzUdpBase::WriteTo(NzPacket* packet, const NzNetAddress& to)
{
    std::string buffer2 = packet->stream.str();
    char* buffer;
    int bufflen;
    union {
        uint32_t i;
        char s[sizeof(uint32_t)];
    } a;
    a.i = htonl(buffer2.size());
    bufflen = sizeof(uint32_t);
    buffer = new char[bufflen+buffer2.size()];
    memcpy(buffer, a.s, sizeof(uint32_t));
    memcpy(buffer+bufflen, buffer2.c_str(), buffer2.size());
    bufflen += buffer2.size();

    int slen = sizeof(to.GetSin().ipv4);
    //int bytes = sendto(m_sock, (char*)(a.s), sizeof(a.s), 0, (sockaddr*)&(to.GetSin().ipv4), slen);
    sendto(m_sock, buffer, bufflen, 0, (sockaddr*)&(to.GetSin().ipv4), slen);
    //std::cout << "sent " << bytes << " " << bufflen << std::endl;
    delete[] buffer;
    return;

	/*if(to.GetProtocol() != m_address.GetProtocol())
    {
        NazaraError("Udp WriteTo failed. NzNetAddress is using a different protocol.");
        return;
    }

    int32_t bytes;
    char* buff = 0;
    int len = buffer2.size();
    if(!m_fixedBuffer) {

        union {
            char buff[4];
            int32_t size;
        } u;
        u.size = htonl(buffer2.size());
        len += 4;

        buff = new char[len];
        std::memcpy(buff, u.buff,4);
        std::memcpy(buff+4, buffer2.c_str(), len-4);

    } else {
        buff = new char[len];
        std::memcpy(buff, buffer2.c_str(), len);
    }
    if(m_fixedBuffer)
    {*/
        /*packet->stream.place(NzArchive::nzBuffer_Reader, 0);
        packet->stream << (uint32_t)packet->stream.str().length();*/
    /*}


    if(to.GetProtocol() == nzSocketProtocol_IPV4) {
        int slen = sizeof(SOCKADDR_IN);
        //int byte = sendto(m_sock, buffer.c_str(), buffer.size(), 0, (sockaddr*)&(to.GetSin().ipv4), len);
        int byte = sendto(m_sock, buff, len, 0, (sockaddr*)&(to.GetSin().ipv4), slen);
        std::cout << byte << "/" << len << " written UDP" << std::endl;
    }
    else if(to.GetProtocol() == nzSocketProtocol_IPV6){
        int slen = sizeof(SOCKADDR_IN6);
        //int byte = sendto(m_sock, buffer.c_str(), buffer.size(), 0, (sockaddr*)&(to.GetSin().ipv6), len);
        int byte = sendto(m_sock, buff, len, 0, (sockaddr*)&(to.GetSin().ipv6), slen);
        std::cout << byte << "/" << len << " written UDP" << std::endl;
    }
    else {
        NazaraError("Udp WriteTo failed. NzNetAddress is using an unknown protocol.");
        return;
    }
*/
}

NzPacket* NzUdpBase::ReadFrom(NzNetAddress& from)
{
    int32_t size = 0, bytes;
    int len;
    char* buffer;
    nzSocketAddr addr;
    len = sizeof(addr.ipv4);
    {
        union {
            int32_t i;
            char b[512];
        } a;
        bytes = recvfrom(m_sock, a.b, sizeof(a.b), MSG_PEEK, reinterpret_cast<sockaddr*>(&addr.ipv4), reinterpret_cast<socklen_t*>(&len));
        size = a.i;
    }
    //std::cout << bytes << " bytes read" << std::endl;
    if(bytes <= 0)
    {
        //std::cout << WSAGetLastError() << std::endl;
        return nullptr;
    }
    size = ntohl(size);
    //std::cout << "bytes to read: " << size << std::endl;

    buffer = new char[size+sizeof(size)];
    bytes = recvfrom(m_sock, buffer, size+sizeof(size), 0, reinterpret_cast<sockaddr*>(&addr.ipv4), reinterpret_cast<socklen_t*>(&len));
    //std::cout << "bytes read: " << bytes << std::endl;
    NzPacket* p = new NzPacket(buffer+sizeof(size), size);

    from.SetSin(addr, m_address.GetProtocol());
    delete[] buffer;
    return p;
    /*
    if(m_address.GetProtocol() == nzSocketProtocol_IPV4) {
        len = sizeof(addr.ipv6);
        if(!m_fixedBuffer) {
            int32_t b = GetBytesAvailable(taille);
            std::cout << b << "/" << taille << " available UDP" << std::endl;
            if(b < taille) {
                return nullptr;
            }

            recvfrom(m_sock, (char*)&size, taille, 0, (sockaddr*)&(addr.ipv4), &len);
            from = NzNetAddress(addr, nzSocketProtocol_IPV4);
            std::cout << "taille reçue: " << size << std::endl;;

        } else {
            size = 64;
            if(GetBytesAvailable(1) < 1) {
                return nullptr;
            }
        }

        buffer = new char[size];
        int byte = recvfrom(m_sock, buffer, size, 0, (sockaddr*)&(addr.ipv4), &len);
        std::cout << "reçu: " << byte << " bytes" << std::endl;
    }
    else if(m_address.GetProtocol() == nzSocketProtocol_IPV6) {
        len = sizeof(SOCKADDR_IN6);
        if(!m_fixedBuffer)
        {
            recvfrom(m_sock, (char*)&size, taille, 0, (sockaddr*)&(addr.ipv6), &len);
            from = NzNetAddress(addr, nzSocketProtocol_IPV6);
        } else {
            size = 64;
        }
        buffer = new char[size];
    }
    else {
        NazaraError("Udp ReadFrom failed. NzNetAddress is using an unknown protocol.");
        return nullptr;
    }

    do {
        bytes = recvfrom(m_sock, buffer+size*(offset-1), size, 0, (sockaddr*)&(addr.ipv6), &len);
        if(bytes <= 0) {
			Sleep(1000);
			timeout++;
		}
		if(m_fixedBuffer && bytes == size) {
		    // The message was too long for the buffer so we extend it
            offset++;
            char* tmp = new char[size*offset];
            std::memset(tmp, 0, size*offset);
            std::memcpy(tmp, buffer, size*(offset-1));
            delete buffer;
            buffer=tmp;
            continue;
		}
    } while(bytes == 0 && timeout < 10);

	buffer[size] = 0;
	NzPacket* p = new NzPacket(buffer, size);
	delete buffer;
	return p;*/
}

void NzUdpBase::Close()
{
    #if defined(USE_WINDOWS)
    	closesocket(m_sock);
    #elif defined(USE_LINUX)
        close(m_sock);
    #endif
}

int32_t NzUdpBase::GetBytesAvailable(uint32_t count)
{
	char* buffer = new char[count];
	SOCKADDR_IN client;
	int len = sizeof(client);
	unsigned long mode = 1;

	#if defined(USE_WINDOWS)
        ioctlsocket(m_sock, FIONBIO, &mode);
    #elif defined(USE_LINUX)
        ioctl(m_sock, FIONBIO, &mode);
    #endif

	int ret = recvfrom(m_sock, buffer, 32, MSG_PEEK, reinterpret_cast<sockaddr*>(&client), reinterpret_cast<socklen_t*>(&len));
	mode = 0;
	
    #if defined(USE_WINDOWS)
        ioctlsocket(m_sock, FIONBIO, &mode);
    #elif defined(USE_LINUX)
        ioctl(m_sock, FIONBIO, &mode);
    #endif
        
	delete buffer;
	return ret;
}
