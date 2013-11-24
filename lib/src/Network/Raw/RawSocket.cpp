#include <Network/Raw/RawSocket.hpp>
#include <Utility.hpp>

NzRawSocket::NzRawSocket(nzSocketProtocol sock, nzNetProtocol net) :
    NzSocket(nzSocketType_RAW, false)
{
    int family = AF_INET;
    if(sock == nzSocketProtocol_IPV6)
        family = AF_INET6;

    int protocol = IPPROTO_ICMP;
    m_sock = socket(family, SOCK_RAW, protocol);
    m_address = NzNetAddress(0,sock);
}

void NzRawSocket::Start()
{
}

void NzRawSocket::Close()
{
    #if defined(USE_WINDOWS)
        closesocket(m_sock);
    #elif defined(USE_LINUX)
        close(m_sock);
    #endif
}

NzPacket* NzRawSocket::Read()
{
    Util::LogManager::error("Cannot Read() a Raw Socket. Use ReadRaw() instead.");
    return nullptr;
}
NzPacket* NzRawSocket::ReadFrom(NzNetAddress& addr)
{
     Util::LogManager::error("Cannot ReadFrom() a Raw Socket. Use ReadRaw() instead.");
    return nullptr;
}
void NzRawSocket::DoAsyncRead()
{
    return;
}

void NzRawSocket::Write(NzPacket* pack)
{
     Util::LogManager::error("Cannot Write() a Raw Socket. Use WriteRaw() instead.");
}
void NzRawSocket::WriteTo(NzPacket* pack, const NzNetAddress& addr)
{
     Util::LogManager::error("Cannot WriteTo() a Raw Socket. Use WriteRaw() instead.");
}
void NzRawSocket::DoAsyncWrite()
{
    return;
}

int32_t NzRawSocket::GetBytesAvailable(uint32_t count)
{
    return 0;
}
