#pragma once

#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

/*!
 * \file Serializable.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 07-08-2012
 */

#include <sstream>
#include <string>

#include <Network/Serialization/Archive.hpp>

/*! \class Serializable
 *  \brief Interface for every serializable object.
 */
class NzSerializable
{
    public:
        NzSerializable();
		virtual ~NzSerializable();
	protected:
		virtual void Serialize(NzArchive& flux) const = 0;
		virtual void Deserialize(NzArchive& flux) = 0;
		virtual int GetID() const = 0;
		virtual int GetVersion() const = 0;


		friend class NzTextArchive;
};

#endif
