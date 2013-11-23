#pragma once
/*
#ifndef TEXTARCHIVE_HPP
#define TEXTARCHIVE_HPP
*/
/*!
 * \file Serializable.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 07-08-2012
 *
 */
/*
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>

#include <Network/generic.hpp>
#include <Network/htonll.hpp>

#include <Network/Serialization/Archive.hpp>
#include <Network/Serialization/Serializable.hpp>

#include <Prerequesites.hpp>
*/
/*! \class TextArchive
	* \brief Archive serializing binary data into a string
	*
	*//*
class NzTextArchive : public NzArchive
{
	public:
		NzTextArchive();
		NzTextArchive(char* buffer, size_t size);
		NzTextArchive(const NzTextArchive& other);

		virtual void clear();
		virtual size_t size() const;
		virtual std::string str() const;

		virtual void operator << (bool b);
		virtual void operator << (int8_t i);
		virtual void operator << (uint8_t i);
		virtual void operator << (int16_t i);
		virtual void operator << (uint16_t i);
		virtual void operator << (int32_t i);
		virtual void operator << (uint32_t i);
		virtual void operator << (int64_t i);
		virtual void operator << (uint64_t i);
		virtual void operator << (double d);
		virtual void operator << (float f);
		virtual void operator << (const char* str);
		virtual NzArchive& operator << (const std::string& str);
		virtual void operator << (const NzSerializable& se);
		virtual void operator << (const NzArchive& Archive);

		virtual void operator >> (bool& b);
		virtual void operator >> (int8_t& i);
		virtual void operator >> (uint8_t& i);
		virtual void operator >> (int16_t& i);
		virtual void operator >> (uint16_t& i);
		virtual void operator >> (int32_t& i);
		virtual void operator >> (uint32_t& i);
		virtual void operator >> (int64_t& i);
		virtual void operator >> (uint64_t& i);
		virtual void operator >> (double& d);
		virtual void operator >> (float& d);
		virtual void operator >> (char* str);
		virtual NzArchive& operator >> (std::string& str);
		virtual void operator >> (NzSerializable& se);

		virtual void place(nzBuffer type, int pos);

	private:
		std::stringstream m_archive;
};

#endif*/
