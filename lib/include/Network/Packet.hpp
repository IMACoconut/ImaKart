#pragma once

#ifndef PACKET_HPP
#define PACKET_HPP

/*!
 * \file Packet.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 08/07/2012
 *
 */

#include <string>
#include <Network/Serialization/Serializable.hpp>
#include <Network/Serialization/TextArchive.hpp>

#include <Utility/Resource.hpp>

/*! \class NzPacket
	* \brief Contains network-transmittable data.
	*/
class NzPacket : public Util::Resource {
    public:

		/*!
			* \fn NzPacket()
			* \brief  Default class constructor.
			*
			*/
		NzPacket();

		NzPacket(const NzPacket& other) = delete;

		/*!
			* \fn NzPacket(const NzSerializable& se)
			* \brief  Class constructor.
			*
			* \param se: Serializable object to send
			*/
		NzPacket(const NzSerializable& se);

		/*!
			* \fn NzPacket(char* buffer, size_t size)
			* \brief  Class constructor.
			*
			* \param buffer: array containing bytes sent/received.
			* \param size: length of the array
			*/
		NzPacket(char* buffer, size_t size);

		/*!
			* \fn NzPacket(const NzTextArchive& s)
			* \brief  Class constructor.
			*
			* \param s: Serialized Archive containing data
			*/
		NzPacket(const NzTextArchive& s);

		/*!
			* \fn virtual ~NzPacket();
			* \brief  Class destructor.
			*/
		virtual ~NzPacket();

        NzPacket& operator=(const NzPacket& other) = delete;


		NzTextArchive stream; /*!< Archive containing packet data */
};

#endif
