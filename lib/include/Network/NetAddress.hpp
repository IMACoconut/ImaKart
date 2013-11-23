#pragma once

#ifndef NETADDRESS_HPP
#define NETADDRESS_HPP

/*!
 * \file NetAddress.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 07-08-2012
 *
 */
#include <Network/generic.hpp>
#include <Network/inet_ntop.hpp>
#include <Network/inet_pton.hpp>
#include <Network/Serialization/Archive.hpp>
#include <Network/Serialization/Serializable.hpp>

#define NETADDRESSID 3
#define NETADDRESSVERSION 1

/*!
	* \struct SocketProtocol
	* \brief Represents the TCP/IP version used.
	*
	*/
typedef enum {
	nzSocketProtocol_IPV4 = 0x0, /*!< IPv4 */
	nzSocketProtocol_IPV6 = 0x1 /*!< IPv6 */
} nzSocketProtocol;

typedef union {
	SOCKADDR_IN ipv4;
	SOCKADDR_IN6 ipv6;
} nzSocketAddr;

/*! \class NzNetAddress
	* \brief Represents a network endpoint.
	*
	*/
class NzNetAddress : public NzSerializable
{
	public:
		/*!
			* \fn NzNetAddress()
			* \brief  Default class constructor.
			*
			*/
		NzNetAddress();

		/*!
			* \fn NzNetAddress(uint16_t port, nzSocketProtocol protocol = nzSocketProtocol_IPV4)
			* \brief  Class constructor.
			*
			* \param port: Port to bind on (server only)
			* \param protocol: Optional - Protocol to use (default: IPv4)
			*/
		NzNetAddress(uint16_t port, nzSocketProtocol protocol = nzSocketProtocol_IPV4);

		/*!
			* \fn NzNetAddress(const std::string& address, uint16_t port, nzSocketProtocol protocol = nzSocketProtocol_IPV4)
			* \brief  Class constructor.
			*
			* \param address: Address to contact/to bind on (client/server)
			* \param port: Port to contact/to bind on (client/server)
			* \param protocol: Optional - Protocol to use (default: IPv4)
			*/
		NzNetAddress(const std::string& address, uint16_t port, nzSocketProtocol protocol = nzSocketProtocol_IPV4);

		/*!
			* \fn NzNetAddress(const nzSocketAddr& sin, nzSocketProtocol protocol = nzSocketProtocol_IPV4)
			* \brief  Class constructor.
			*
			* \param sin: C-Style structure containing address' data to extract.
			* \param protocol: Optional - Protocol to use (default: IPv4)
			*/
		NzNetAddress(const nzSocketAddr& sin, nzSocketProtocol protocol = nzSocketProtocol_IPV4);

		/*!
			* \fn nzSocketProtocol GetProtocol() const
			* \brief  getter
			*
			* \return Returns Address' protocol
			*/
		nzSocketProtocol GetProtocol() const;

		/*!
			* \fn const nzSOCKADDR_IN& GetSin() const
			* \brief  getter
			*
			* \return Returns read-only reference to the m_sin member
			*/
		const nzSocketAddr& GetSin() const;

		void SetSin(const nzSocketAddr& addr, nzSocketProtocol protocol);

		/*!
			* \fn virtual void Serialize(Archive& Archive) const
			* \brief put all the object's informations into a Archive
			*
			* \param Archive: Archive to serialize in
			*/
		virtual void Serialize(NzArchive& Archive) const;

		/*!
			* \fn virtual void Deserialize(Archive& Archive)
			* \brief get all the object's informations from a Archive
			*
			* \param Archive: Archive to deserialize from
			*/
		virtual void Deserialize(NzArchive& Archive);

		/*!
			* \fn virtual int GetID() const
			* \brief  getter
			*
			* \return Returns the class ID
			*/
		virtual int GetID() const;

		/*!
			* \fn virtual int GetVersion() const
			* \brief  getter
			*
			* \return Returns the class version
			*/
		virtual int GetVersion() const;

		virtual const std::string& GetAddress() const;

		virtual uint16_t GetPort() const;

    protected:
        /*!
			* \fn virtual bool Equals(NzNetAddress& other)
			* \brief  check if the other and current addresses refers to the same ip/port
			*
			* \param other: netaddress to compare.
			* \return Returns true if other and currend refers to the same ip/port
			*/
        virtual bool Equals(NzNetAddress& other);

	private:
        int CreateSinAddr(const std::string& address, sockaddr_in& dest);

		std::string m_address; /*!< Represents the remote address (client/server) or the address to bind on (server only)*/
		uint16_t m_port; /*!< Represents the remote port (client/server) or the port to bind on (server only) */
		nzSocketProtocol m_protocol; /*!< Represents the transmission protocol (IPv4/6) */
		nzSocketAddr m_sin;  /*!< Union containing a C-Style structure representing the connection */

    friend bool operator==(NzNetAddress& addr, NzNetAddress& other);
};

bool operator==(NzNetAddress& addr, NzNetAddress& other);

#endif
