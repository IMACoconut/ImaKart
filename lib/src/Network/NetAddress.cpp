#include <Network/NetAddress.hpp>
#include <iostream>
#include <cstring>

NzNetAddress::NzNetAddress() :
    NzNetAddress("127.0.0.1", 27018, nzSocketProtocol_IPV4)
{
}

NzNetAddress::NzNetAddress(uint16_t port, nzSocketProtocol protocol) :
	m_address("any"), m_port(port), m_protocol(protocol), m_sin()
{
	if(protocol == nzSocketProtocol_IPV4) {
		m_sin.ipv4.sin_addr.s_addr	= INADDR_ANY;
		m_sin.ipv4.sin_family = AF_INET;
		m_sin.ipv4.sin_port		= htons(port);	
	}
	else if(protocol == nzSocketProtocol_IPV6) {
		m_sin.ipv6.sin6_addr	= in6addr_any;
		m_sin.ipv6.sin6_family = AF_INET6;
		m_sin.ipv6.sin6_port		= htons(port);
	}
}

NzNetAddress::NzNetAddress(const std::string& address, uint16_t port, nzSocketProtocol protocol):
	m_address(address), m_port(port), m_protocol(protocol), m_sin()
{
	if(protocol == nzSocketProtocol_IPV4) {
        CreateSinAddr(address, m_sin.ipv4);
		m_sin.ipv4.sin_port		= htons(port);
	}
	else if(protocol == nzSocketProtocol_IPV6) {
		inet_pton(AF_INET6, m_address.c_str(), (unsigned char*)&m_sin.ipv6.sin6_addr);
		m_sin.ipv6.sin6_family = AF_INET6;
		m_sin.ipv6.sin6_port = htons(port);
	}
}

NzNetAddress::NzNetAddress(const nzSocketAddr& sin, nzSocketProtocol protocol) :
	m_address(""), m_port(0), m_protocol(protocol), m_sin(sin)
{
	if(protocol == nzSocketProtocol_IPV4) {
		m_address = std::string(inet_ntoa(m_sin.ipv4.sin_addr));
		m_port = ntohs(m_sin.ipv4.sin_port);

	}
	else
	{
		char str[INET_ADDRSTRLEN];
		m_port = ntohs(m_sin.ipv6.sin6_port);
		inet_ntop(AF_INET6, &(m_sin.ipv6.sin6_addr), str, INET6_ADDRSTRLEN);
		m_address = std::string(str);
	}
}

nzSocketProtocol NzNetAddress::GetProtocol() const
{
	return m_protocol;
}

const nzSocketAddr& NzNetAddress::GetSin() const
{
	return m_sin;
}

void NzNetAddress::SetSin(const nzSocketAddr& addr, nzSocketProtocol protocol)
{
    m_protocol = protocol;
    m_sin = addr;
    if(protocol == nzSocketProtocol_IPV4)
    {
		m_address = std::string(inet_ntoa(addr.ipv4.sin_addr));
		m_port = ntohs(addr.ipv4.sin_port);
    }
	else
	{
		char str[INET_ADDRSTRLEN];
		m_port = ntohs(addr.ipv6.sin6_port);
		inet_ntop(AF_INET6, const_cast<IN6_ADDR*>(&(addr.ipv6.sin6_addr)), str, INET6_ADDRSTRLEN);
		m_address = std::string(str);
	}
}

void NzNetAddress::Serialize(NzArchive& stream) const
{
	stream << m_address;
	stream << m_port;
	union {
        int i;
        nzSocketProtocol p;
	} a;
	a.p = m_protocol;
	stream << a.i;
}

void NzNetAddress::Deserialize(NzArchive& stream)
{
	stream >> m_address;
	stream >> m_port;
	union {
        int i;
        nzSocketProtocol p;
	} a;
	stream >> a.i;
	m_protocol = a.p;
}

int NzNetAddress::GetID() const
{
	return NETADDRESSID;
}

int NzNetAddress::GetVersion() const
{
	return NETADDRESSVERSION;
}

const std::string& NzNetAddress::GetAddress() const
{
    return m_address;
}

uint16_t NzNetAddress::GetPort() const
{
    return m_port;
}

bool NzNetAddress::Equals(NzNetAddress& other) {
    return (m_address == other.m_address && m_port == other.m_port && m_protocol == other.m_protocol);
}

bool operator==(NzNetAddress& addr, NzNetAddress& other)
{
    return addr.Equals(other);
}

int NzNetAddress::CreateSinAddr(const std::string& address, sockaddr_in& dest)
{
    memset(&dest, 0, sizeof(dest));
    unsigned int addr = inet_addr(address.c_str());

    if (addr != INADDR_NONE) {
        dest.sin_addr.s_addr = addr;
        dest.sin_family = AF_INET;
    }
    else {
        hostent* hp = gethostbyname(address.c_str());
        if (hp != 0) {
            memcpy(&(dest.sin_addr), hp->h_addr, hp->h_length);
            dest.sin_family = hp->h_addrtype;
        }
        else {
            return 0;
        }
    }
    return 1;
}
