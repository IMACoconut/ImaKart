#include <Network/Udp/UdpListener.hpp>

NzUdpListener::NzUdpListener(const NzNetAddress& address): NzUdpSocket(address)
{
    Start();
}

void NzUdpListener::Start()
{
    bind(m_sock, (SOCKADDR *)&m_address.GetSin(), sizeof(m_address.GetSin()));
}
