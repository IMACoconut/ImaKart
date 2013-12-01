#include <Network/Utilities/PingService.hpp>
#include <Utility/Clock.hpp>

NzPing NzPingService::Ping(const NzNetAddress& addr)
{
    std::cout << "begin" << std::endl;
    Util::Clock clock;
	NzICMPHeader header = BuildICMPHeader(static_cast<uint32_t>(clock.GetMilliseconds()), "Nazara Network Engine Ping Echo ");
    NzIPHeader ipheader;
    std::cout << 1 << std::endl;
    NzRawSocket sock(addr.GetProtocol(), nzNetProtocol_ICMP);
    sock.WriteRaw(header, addr);
    std::cout << 2 << std::endl;
    NzNetAddress from;
    while(clock.GetSeconds() < 3){
        int bytes = sock.ReadRaw(ipheader, from);
        if(bytes != sizeof(NzIPHeader))
            continue;

        // Not a ping
        if(ipheader.proto != nzNetProtocol_ICMP)
            continue;

        // Not a ping from our program.
        if(ipheader.icmp.id != header.id)
            continue;

        std::cout << "end" << std::endl;
        switch(ipheader.icmp.type) {
            case nzICMPCode_EchoReply:
				return NzPing(nzPingStatus_ok, static_cast<uint32_t>(clock.GetMilliseconds() - header.timestamp));
            case nzICMPCode_TTLExpire:
                return NzPing(nzPingStatus_ttlExpire, ipheader.ttl);
            case nzICMPCode_DestUnreach:
                return NzPing(nzPingStatus_hostUnreachable, 0);
            default:
                return NzPing(nzPingStatus_error, 0);
        }
    }
    std::cout << "end" << std::endl;
    return NzPing(nzPingStatus_ttlExpire, 0);
}
