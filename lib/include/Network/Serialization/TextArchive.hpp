#pragma once

#ifndef TEXTARCHIVE_HPP
#define TEXTARCHIVE_HPP

/*!
 * \file Serializable.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 07-08-2012
 *
 */

#include <sstream>
#include <string>
#include <cstring>
#include <iostream>

#include <Network/generic.hpp>
#include <Network/htonll.hpp>

#include <Network/Serialization/Archive.hpp>
#include <Network/Serialization/Serializable.hpp>

/*! \class TextArchive
	* \brief Archive serializing binary data into a string
	*
	*/
class NzTextArchive : public NzArchive
{
	public:
		NzTextArchive();
		NzTextArchive(char* buffer, size_t size);
		NzTextArchive(const NzTextArchive& other);

		virtual void clear();
		virtual size_t size() const;
		virtual std::string str() const;

		virtual NzArchive& operator << (bool b);
		virtual NzArchive& operator << (int8_t i);
		virtual NzArchive& operator << (uint8_t i);
		virtual NzArchive& operator << (int16_t i);
		virtual NzArchive& operator << (uint16_t i);
		virtual NzArchive& operator << (int32_t i);
		virtual NzArchive& operator << (uint32_t i);
		virtual NzArchive& operator << (int64_t i);
		virtual NzArchive& operator << (uint64_t i);
		virtual NzArchive& operator << (double d);
		virtual NzArchive& operator << (float f);
		virtual NzArchive& operator << (const char* str);
		virtual NzArchive& operator << (const std::string& str);
		virtual NzArchive& operator << (const NzSerializable& se);
		virtual NzArchive& operator << (const NzArchive& Archive);

		virtual NzArchive& operator >> (bool& b);
		virtual NzArchive& operator >> (int8_t& i);
		virtual NzArchive& operator >> (uint8_t& i);
		virtual NzArchive& operator >> (int16_t& i);
		virtual NzArchive& operator >> (uint16_t& i);
		virtual NzArchive& operator >> (int32_t& i);
		virtual NzArchive& operator >> (uint32_t& i);
		virtual NzArchive& operator >> (int64_t& i);
		virtual NzArchive& operator >> (uint64_t& i);
		virtual NzArchive& operator >> (double& d);
		virtual NzArchive& operator >> (float& d);
		virtual NzArchive& operator >> (char* str);
		virtual NzArchive& operator >> (std::string& str);
		virtual NzArchive& operator >> (NzSerializable& se);

		virtual void place(nzBuffer type, int pos);

	private:
		std::stringstream m_archive;
};

#endif
