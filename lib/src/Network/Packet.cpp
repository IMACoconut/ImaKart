#include <Network/Packet.hpp>

NzPacket::NzPacket() : stream() {
}

NzPacket::NzPacket(const NzSerializable& se) : stream()
{
	stream << se;
}

NzPacket::NzPacket(char* buffer, size_t size) : stream(buffer, size) {
}

NzPacket::NzPacket(const NzTextArchive& s) : stream(s) {
}

NzPacket::~NzPacket()
{
}