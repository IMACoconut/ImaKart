#pragma once

#ifndef UDPLISTENER_HPP
#define UDPLISTENER_HPP

/*!
 * \file UdpListener.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 08/07/2012
 */

#include <Network/Udp/UdpSocket.hpp>
#include <Network/NetAddress.hpp>

/*! \class NzUdpListener
	* \brief Class representing a non-connected socket using UDP protocol.
	*/
class NzUdpListener : public NzUdpSocket
{
    public:

		/*!
			* \fn NzUdpListener(const NzNetAddress& address)
			* \brief  Class constructor.
			* \param address: address, port, protocol of the connection.
			*/
        NzUdpListener(const NzNetAddress& address);

		/*!
			* \fn virtual void Start()
			* \brief Starts socket (listen on the port/address specified on constructor)
			*/
        virtual void Start();
};

#endif
