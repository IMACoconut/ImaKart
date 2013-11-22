#pragma once

#ifndef RAWSOCKET_HPP
#define RAWSOCKET_HPP

/*!
 * \file RawSocket.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 08/07/2012
 */

#include <Network/Socket.hpp>
#include <Network/Raw/RawPacket.hpp>
#include <iostream>

/*! \class NzRawSocket
	* \brief Class representing a connected socket using TCP protocol.
	*/
class NzRawSocket : public NzSocket
{
    public:

		/*!
			* \fn NzRawSocket(nzSocketProtocol sock, nzNetProtocol net)
			* \brief  Class constructor.
			*
			*/
        NzRawSocket(nzSocketProtocol sock, nzNetProtocol net);

		/*!
			* \fn virtual void start()
			* \brief Starts socket (attempts to connect to the remote host)
			*/
        virtual void Start();

        virtual void Close();

        template <typename T>
        int32_t ReadRaw(T& data, NzNetAddress& from)
        {
            if(m_address.GetProtocol() == nzSocketProtocol_IPV4) {
                int32_t size2 = sizeof(from.GetSin().ipv4);
                return recvfrom(m_sock, (char*)&data, sizeof(T), 0, (SOCKADDR*)&(from.GetSin().ipv4), reinterpret_cast<socklen_t*>(&size2));
            } else {
                int32_t size2 = sizeof(from.GetSin().ipv6);
                return recvfrom(m_sock, (char*)&data, sizeof(T), 0, (SOCKADDR*)&(from.GetSin().ipv6), reinterpret_cast<socklen_t*>(&size2));
            }
        }

        template <typename T>
        int32_t WriteRaw(T data, const NzNetAddress& to)
        {
            if(m_address.GetProtocol() == nzSocketProtocol_IPV4)
                return sendto(m_sock, (char*)&data, sizeof(T), 0, (SOCKADDR*)&(to.GetSin().ipv4), sizeof(to.GetSin().ipv4));
            else
                return sendto(m_sock, (char*)&data, sizeof(T), 0, (SOCKADDR*)&(to.GetSin().ipv6), sizeof(to.GetSin().ipv6));
        }


        virtual NzPacket* Read();
        virtual NzPacket* ReadFrom(NzNetAddress& from);
        virtual void DoAsyncRead();
        virtual void Write(NzPacket* packet);
        virtual void WriteTo(NzPacket* packet, const NzNetAddress& to);
        virtual void DoAsyncWrite();
        virtual int32_t GetBytesAvailable(uint32_t count = 32);

	protected:

	private:
		/*!
			* \fn NzRawSocket(const NzRawSocket& other) = delete
			* \brief  Copy constructor disabled.
			*/
		NzRawSocket(const NzRawSocket& other);
};

#endif
