#pragma once

#ifndef RAWPACKET_HPP
#define RAWPACKET_HPP

#include <stdint.h>
#include <string>

typedef enum {
    nzNetProtocol_ICMP = 1
} nzNetProtocol;

typedef enum {
    nzICMPCode_EchoReply = 0,
    nzICMPCode_EchoRequest = 8,
    nzICMPCode_TTLExpire = 11,
    nzICMPCode_DestUnreach = 3
} nzICMPCode;

struct NzICMPHeader {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t id;
    uint16_t seq;
    uint32_t timestamp;
    uint8_t data[32];
};


struct NzIPHeader {
    uint8_t h_len:4;           // Length of the header in dwords
    uint8_t version:4;         // Version of IP
    uint8_t tos;               // Type of service
    uint16_t total_len;       // Length of the packet in dwords
    uint16_t ident;           // unique identifier
    uint16_t flags;           // Flags
    uint8_t ttl;               // Time to live
    uint8_t proto;             // Protocol number (TCP, UDP etc)
    uint16_t checksum;        // IP checksum
    uint32_t source_ip;
    uint32_t dest_ip;
    union {
        NzICMPHeader icmp;
    };
};

void printIPPacket(const NzIPHeader& header);

uint16_t CalculateChecksum(uint16_t* buffer, int nbytes);

NzICMPHeader BuildICMPHeader(uint32_t timestamp, const std::string& msg);

#endif // NETWORKUTILITIES_HPP
