#pragma once

#ifndef NETWORKUTILITIES_HPP
#define NETWORKUTILITIES_HPP

#include <Network/generic.hpp>
#include <Network/Socket.hpp>
#include <Network/Raw/RawSocket.hpp>

typedef enum {
    nzPingStatus_ok = 0,
    nzPingStatus_notYet = 1,
    nzPingStatus_hostUnreachable = 2,
    nzPingStatus_bufferError = 3,
    nzPingStatus_error = 4,
    nzPingStatus_ttlExpire = 5,
    nzPingStatus_notInitialized = 6
} nzPingStatus;

struct NzPing
{
    NzPing(nzPingStatus s, int16_t t): status(s),ms(t) {}
    NzPing() : status(nzPingStatus_notInitialized), ms(-1) {}

    nzPingStatus status;
    int16_t ms;
};

struct NzAsyncPingData;

class NzPingService
{
    public:
        NzPingService() = delete;

        ~NzPingService() = delete;

        static NzPing Ping(const NzNetAddress& addr);

};
#endif // NETWORKUTILITIES_HPP
