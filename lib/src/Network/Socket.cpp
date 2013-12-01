#include <Network/Socket.hpp>

NzSocket::NzSocket(nzSocketType type, bool fixedBuffer) :
    NzSocket(NzNetAddress(), 0, type, fixedBuffer)
{
/*    m_timeout.Restart();
    m_timeout.Pause();*/
    //std::cout << "socket: " << m_fixedBuffer << std::endl;
}

NzSocket::NzSocket(const NzNetAddress& addr, nzSocketType type, bool fixedBuffer) :
    NzSocket(addr, 0, type, fixedBuffer)
{
    //std::cout << "socket: " << m_fixedBuffer << std::endl;
}

NzSocket::NzSocket(const NzNetAddress& addr, SOCKET sock, nzSocketType type, bool fixedBuffer) :
    m_type(type), m_address(addr), m_sock(sock), m_fixedBuffer(fixedBuffer),
    m_nonBlocking(true), m_allowBroadcast(false), m_hasTimedOut(false), m_lastKnownPing(5)
{
    #ifdef USE_WINDOWS
        m_eventsHandler = WSACreateEvent();
    #endif
}

NzSocket::~NzSocket()
{
    #ifdef USE_WINDOWS
        WSACloseEvent(m_eventsHandler);
    #endif
}

nzSocketType NzSocket::GetProtocol() const
{
	return m_type;
}

void NzSocket::AsyncRead()
{
	return;
}

void NzSocket::SetAsyncReadCallback(std::function<void (NzPacket*)> func)
{
	m_asyncReadCallback = func;
}

void NzSocket::AsyncWrite(NzPacket* packet)
{
	packet->grab();
	m_asyncWrite.push(packet);
}

void NzSocket::SetAsyncWriteCallback(std::function<void (int)> func)
{
	m_asyncWriteCallback = func;
}

void NzSocket::UpdateAsync()
{
	DoAsyncRead();
	DoAsyncWrite();
}

bool NzSocket::IsBufferFixed() const
{
    return m_fixedBuffer;
}

void NzSocket::SetBufferFixed(bool fixed)
{
    m_fixedBuffer = fixed;
}

void NzSocket::SetNonBlocking(bool nonblock)
{
    unsigned long mode = 1;
    if(!nonblock)
        mode = 0;
    #ifdef USE_WINDOWS
	   ioctlsocket(m_sock, FIONBIO, &mode);
    #elif defined USE_LINUX
        ioctl(m_sock, FIONBIO, &mode);
    #endif
	m_nonBlocking = nonblock;
}

void NzSocket::AllowBroadcast(bool allow)
{
    unsigned long mode = 1;
    if(!allow)
        mode = 0;

    setsockopt(m_sock,SOL_SOCKET,SO_BROADCAST,(char*)&mode,4);

    m_allowBroadcast = allow;
}

bool NzSocket::IsBroadcastAllowed() const
{
    return m_allowBroadcast;
}

bool NzSocket::IsNonBlocking() const
{
    return m_nonBlocking;
}

bool NzSocket::IsTimeout() const
{
    return !m_hasTimedOut;//m_timeout.GetSeconds() > 10;
}

const NzNetAddress& NzSocket::GetBindAddress() const
{
    return m_address;
}

int32_t NzSocket::GetPing() const
{
    return m_lastKnownPing;
}
