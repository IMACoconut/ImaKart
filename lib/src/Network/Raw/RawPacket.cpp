#include <Network/Raw/RawPacket.hpp>
#include <iostream>

void printIPPacket(const NzIPHeader& header)
{
    std::cout << "version: " << (int)header.version << std::endl;
    std::cout << "length: " << (int)header.h_len << std::endl;
    std::cout << "protocol: " << (int)header.proto << std::endl;
}

uint16_t CalculateChecksum(uint16_t* buffer, int nbytes)
{
    uint32_t sum;
    sum = 0;
    while (nbytes > 1) {
        sum += *buffer++;
        nbytes -= sizeof(uint16_t);
    }

    if (nbytes)
        sum += *(uint8_t*)buffer;

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    return (uint16_t)(~sum);
}
NzICMPHeader BuildICMPHeader(uint32_t timestamp, const std::string& msg)
{
        NzICMPHeader header;
        header.type = nzICMPCode_EchoRequest;
        header.code = 0;
        header.checksum = 0;
        
        #if defined USE_WINDOWS
            header.id = (uint8_t)GetCurrentProcessId();
        #elif defined USE_LINUX
            header.id = (uint8_t)getpid();
        #else 
            header.id = 0;
        #endif

        header.seq = rand();
        header.timestamp = timestamp;
        //sprintf((char*)header.data, msg.c_str());
        header.checksum = CalculateChecksum((uint16_t*)&header, sizeof(NzICMPHeader));
        return header;
}
