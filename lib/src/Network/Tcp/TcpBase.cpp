#include <Network/Tcp/TcpBase.hpp>
#include <Utility.hpp>

#include <iostream>

NzTcpBase::NzTcpBase() : NzSocket(nzSocketType_TCP),
			m_currentReadSize(0), m_currentReadLeft(0), m_currentWriteSize(0),
			m_currentWriteLeft(0)
{
	if(m_address.GetProtocol() == nzSocketProtocol_IPV6)
		m_sock = socket(AF_INET6,SOCK_STREAM, 0);
	else if(m_address.GetProtocol() == nzSocketProtocol_IPV4)
		m_sock = socket(AF_INET,SOCK_STREAM, 0);
}

NzTcpBase::NzTcpBase(const NzNetAddress& address, bool fixedBuffer) : NzSocket(address, nzSocketType_TCP, fixedBuffer),
	m_currentReadSize(0), m_currentReadLeft(0), m_currentWriteSize(0),
	m_currentWriteLeft(0)
{
    //std::cout << "base: " << fixedBuffer << " " << m_fixedBuffer << std::endl;
	if(address.GetProtocol() == nzSocketProtocol_IPV6)
		m_sock = socket(AF_INET6,SOCK_STREAM, 0);
	else if(address.GetProtocol() == nzSocketProtocol_IPV4)
		m_sock = socket(AF_INET,SOCK_STREAM, 0);
}

NzTcpBase::NzTcpBase(const NzNetAddress& address, SOCKET sock, bool fixedBuffer)
    : NzSocket(address, sock, nzSocketType_TCP, fixedBuffer),
    m_currentReadSize(0), m_currentReadLeft(0),
    m_currentWriteSize(0), m_currentWriteLeft(0)
    { }

NzTcpBase::~NzTcpBase(void)
{
	Close();
}

NzPacket* NzTcpBase::Read()
{
	int32_t size = 0, finalSize = 0, byte = 0, taille = sizeof(size);
	char* buffer = nullptr;
	int flags = 0;
	if(!m_fixedBuffer)
	{
	    // If we're not in nonblock mode we set the flag to MSG_WAITALL
	    // so the recv function will wait to have the whole data before reading it.
	    // If in nonblock mode the flag will cause the recv() function to return -1
	    // even if there is readable data to read.
	    if(!m_nonBlocking)
            flags = MSG_WAITALL;
        byte = recv(m_sock, (char*)&size, taille, flags);
        // byte should be equal to taille, otherwise a connection problem occured.
        if(byte <= 0) {
            /*NzPing p = NzPingService::Ping(this->GetBindAddress());
            if(p.status == nzPingStatus_ok)
            {
                m_lastKnownPing = p.ms;
                m_hasTimedOut = false;
            }
            else if(p.status == nzPingStatus_hostUnreachable)
                m_hasTimedOut = true;*/

            return nullptr;
        }

        size = ntohl(size);
        buffer = new char[size];

        byte = recv(m_sock, buffer, size, flags);
        // byte should be equal to size, otherwise a sending problem occured.
        if(byte != size || byte <= 0) {
            Util::LogManager::error("Erreur de réception TCP.");
            delete[] buffer;
            return nullptr;
        }
        finalSize = size;
	}
	else {
	    // Arbitrary packet size.
        size = 64;

        char* buffer = new char[size];
        int offset = 0;
        do {
            byte = recv(m_sock, buffer+size*offset, size, 0);

            if(byte <= 0) {
                NzPing p = NzPingService::Ping(this->GetBindAddress());
                if(p.status == nzPingStatus_ok)
                {
                    m_lastKnownPing = p.ms;
                    m_hasTimedOut = false;
                }
                else if(p.status == nzPingStatus_hostUnreachable)
                    m_hasTimedOut = true;

                delete[] buffer;
                return nullptr;
            }

            // The message was too long for the buffer so we extend it
            if(byte == size) {
                offset++;
                char* tmp = new char[size*offset];
                std::memset(tmp, 0, size*offset);
                std::memcpy(tmp, buffer, size*(offset-1));
                delete buffer;
                buffer=tmp;

                finalSize += size;
            }
        } while(byte == size);

	}

	NzPacket* p = new NzPacket(buffer, finalSize);
	delete[] buffer;
	return p;
}

NzPacket* NzTcpBase::ReadFrom(NzNetAddress& from)
{
    from = m_address;
    return Read();
}

void NzTcpBase::DoAsyncRead()
{
	int b = GetBytesAvailable();

	if(!m_currentReadSize && b < (int)sizeof(m_currentReadSize)) {
	    // Nothing to read on the socket
		return;
	}
	else if(!m_currentReadSize) {
	    // New incoming data
        if(!m_fixedBuffer)
        {
            // Trick to keep the binary value of size.
            union {
                char buff[4];
                int32_t size;
            } u;
            recv(m_sock, u.buff, sizeof(int32_t), MSG_WAITALL);
            m_currentReadSize = ntohl(u.size);
            m_readBuffer = new char[m_currentReadSize];
            m_currentReadLeft = m_currentReadSize;
        }
        else {
            m_currentReadSize = 64;
            m_currentReadLeft = 64;
            m_readBuffer = new char[m_currentReadLeft];
        }
    }
    if(!m_fixedBuffer)
    {
        b = GetBytesAvailable(m_currentReadLeft);
        if(b < m_currentReadLeft) {
            return;
        }

        int decal = m_currentReadSize-m_currentReadLeft;

        int bytes = recv(m_sock, m_readBuffer+decal, m_currentReadLeft, MSG_WAITALL);
        if(bytes < m_currentReadLeft)
        {
            m_currentReadLeft -= bytes;
            return;
        }
    }
    else {
        b = GetBytesAvailable(1);
        if(b == 0)
            return;

        int decal = m_currentReadSize-m_currentReadLeft;
        int bytes = 0;
        do {
            bytes = recv(m_sock, m_readBuffer+decal, m_currentReadLeft, 0);
            if(bytes == 0)
                return;
            if(bytes == m_currentReadLeft) {
                m_currentReadSize += m_currentReadLeft;
                char* tmp = new char[m_currentReadSize];
                std::memset(tmp, 0, m_currentReadSize);
                std::memcpy(tmp, m_readBuffer, m_currentReadSize-m_currentReadLeft);
                delete m_readBuffer;
                m_readBuffer=tmp;
            }
        } while(bytes == m_currentReadLeft);
    }

	m_readBuffer[m_currentReadSize] = 0;
	NzPacket* p = new NzPacket(m_readBuffer, m_currentReadSize);
	m_currentReadSize = 0;
	delete[] m_readBuffer;
	m_asyncReadCallback(p);
}

void NzTcpBase::Write(NzPacket* packet)
{
    // Packet lock to make sure it will not be destroyed by another thread.
	packet->grab();
	/*std::string str(packet->stream.str());
	NzByteArray tmp((const uint8_t*)str.GetConstBuffer(), str.GetSize());
    NzByteArray buffer;
    buffer.Insert(0, tmp);
    if(!m_fixedBuffer)
    {
        uint8_t size = tmp.GetSize();
        buffer.Insert(0, &size, 1);
    }*/


	std::string buffer2 = packet->stream.str();
    char* buff = 0;
    int32_t bytes;
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

	bytes = send(m_sock, buff, len, 0);
	//int bytes = send(m_sock, (char*)buffer.GetBuffer(), buffer.GetSize(), 0);
	if(bytes <= 0) {
        std::cout << bytes << std::endl;
	}
    delete[] buff;
	packet->drop();
}

void NzTcpBase::WriteTo(NzPacket* p, const NzNetAddress& to)
{
    Write(p);
}

void NzTcpBase::DoAsyncWrite()
{
	if(!m_currentWriteSize && m_asyncWrite.empty()) {
	    //Nothing to send
		return;
	}
	else if(!m_currentWriteSize)
	{
		NzPacket* packet = m_asyncWrite.front();
		m_asyncWrite.pop();
		std::string buffer = packet->stream.str();
		m_currentWriteSize = buffer.length();

        if(!m_fixedBuffer)
        {
            union {
                char buff[4];
                int32_t size;
            } u;
            u.size = htonl(buffer.length());
            m_writeBuffer = new char[u.size+4];
            std::memcpy(m_writeBuffer, u.buff, 4);
            std::memcpy(m_writeBuffer+4, buffer.c_str(), m_currentWriteSize);
            m_currentWriteSize +=4;
        }
		else {
            m_writeBuffer = new char[buffer.length()];
            std::memcpy(m_writeBuffer, buffer.c_str(), m_currentWriteSize);
		}
		m_currentWriteLeft = m_currentWriteSize;
		packet->drop();
	}
	int decal = m_currentWriteSize - m_currentWriteLeft;
	int bytes = send(m_sock, m_writeBuffer+decal, m_currentWriteLeft, 0);
	if(bytes < 0) {
	    // Error while sending the packet. The callback will hold -1.
        m_asyncWriteCallback(-1);
	}
    if(bytes < m_currentWriteLeft)
	{
		m_currentWriteLeft -= bytes;
		return;
	}

	delete[] m_writeBuffer;
	m_currentWriteSize = 0;

	m_asyncWriteCallback(0);
}

void NzTcpBase::Close()
{
    #if defined(USE_WINDOWS)
	closesocket(m_sock);
    #elif defined(USE_LINUX)
    close(m_sock);
    #endif
}
/*
std::vector<std::string> NzTcpBase::GetBindableAddresses()
{
	char ac[80];
	std::vector<std::string> addresses;
	if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
		return addresses;
	}
	struct hostent *phe = gethostbyname(ac);
	if (phe == 0) {
		return addresses;
	}

	for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
		struct in_addr addr;
		memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
		addresses.push_back(inet_ntoa(addr));
	}

	return addresses;
}*/


int32_t NzTcpBase::GetBytesAvailable(uint32_t count)
{
	char* buffer = new char[count];
	bool nb = m_nonBlocking;
	if(!nb)
         SetNonBlocking(true);

	int32_t ret = recv(m_sock, buffer, count, MSG_PEEK);
	if(!nb)
        SetNonBlocking(false);

    m_nonBlocking = nb;
	delete[] buffer;
	return ret;
}