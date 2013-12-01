#pragma once

#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

/*!
 * \file Serializable.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 07-08-2012
 *
 */

#include <sstream>
#include <string>
class NzSerializable;
/*! \class Archive
	* \brief Abstract base class for every Archive
	*
	*/
class NzArchive
{
	public:
		typedef enum {
			nzBuffer_Reader,
			nzBuffer_Writer
		} nzBuffer;
		virtual void clear() = 0;
		virtual size_t size() const = 0;
		virtual std::string str() const = 0;

		virtual NzArchive& operator << (bool b) = 0;
		virtual NzArchive& operator << (int8_t i) = 0;
		virtual NzArchive& operator << (uint8_t i) = 0;
		virtual NzArchive& operator << (int16_t i) = 0;
		virtual NzArchive& operator << (uint16_t i) = 0;
		virtual NzArchive& operator << (int32_t i) = 0;
		virtual NzArchive& operator << (uint32_t i) = 0;
		virtual NzArchive& operator << (int64_t i) = 0;
		virtual NzArchive& operator << (uint64_t i) = 0;
		virtual NzArchive& operator << (double d) = 0;
		virtual NzArchive& operator << (float f) = 0;
		virtual NzArchive& operator << (const char* str) = 0;
		virtual NzArchive& operator << (const std::string& str) = 0;
		virtual NzArchive& operator << (const NzSerializable& se) = 0;
		virtual NzArchive& operator << (const NzArchive& Archive) = 0;

		virtual NzArchive& operator >> (bool& b) = 0;
		virtual NzArchive& operator >> (int8_t& i) = 0;
		virtual NzArchive& operator >> (uint8_t& i) = 0;
		virtual NzArchive& operator >> (int16_t& i) = 0;
		virtual NzArchive& operator >> (uint16_t& i) = 0;
		virtual NzArchive& operator >> (int32_t& i) = 0;
		virtual NzArchive& operator >> (uint32_t& i) = 0;
		virtual NzArchive& operator >> (int64_t& i) = 0;
		virtual NzArchive& operator >> (uint64_t& i) = 0;
		virtual NzArchive& operator >> (double& d) = 0;
		virtual NzArchive& operator >> (float& d) = 0;
		virtual NzArchive& operator >> (char* str) = 0;
		virtual NzArchive& operator >> (std::string& str) = 0;
		virtual NzArchive& operator >> (NzSerializable& se) = 0;

		virtual void place(nzBuffer type, int pos) = 0;

	protected:
		NzArchive();
		NzArchive(const NzArchive& other) = delete;
		virtual ~NzArchive();
};

#endif
