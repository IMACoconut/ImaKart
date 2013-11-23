#include <Network/Serialization/TextArchive.hpp>
#include <Utility.hpp>

NzTextArchive::NzTextArchive() : NzArchive(), m_archive() {	}
NzTextArchive::NzTextArchive(char* buffer, size_t size) : NzArchive(), m_archive()
{
	m_archive.write(buffer, size);
}
NzTextArchive::NzTextArchive(const NzTextArchive& other) : NzArchive(), m_archive(other.m_archive.str()) { }

void NzTextArchive::clear()
{
	m_archive.clear();
}

size_t NzTextArchive::size() const
{
	return m_archive.str().size();
}

std::string NzTextArchive::str() const
{
	return m_archive.str();
}

NzArchive& NzTextArchive::operator << (bool b)
{
	m_archive.write((char*)&b, sizeof(bool));
	return *this;
}

NzArchive& NzTextArchive::operator << (int8_t i)
{
	m_archive.write((const char*)&i, sizeof(int8_t));
	return *this;
}

NzArchive& NzTextArchive::operator << (uint8_t i)
{
	m_archive.write((const char*)&i, sizeof(uint8_t));
	return *this;
}

NzArchive& NzTextArchive::operator << (int16_t i)
{
    i = htons(i);
	m_archive.write((const char*)&i, sizeof(int16_t));
	return *this;
}

NzArchive& NzTextArchive::operator << (uint16_t i)
{
    i = htons(i);
	m_archive.write((const char*)&i, sizeof(uint16_t));
	return *this;
}

NzArchive& NzTextArchive::operator << (int32_t i)
{
    i = htonl(i);
	m_archive.write((const char*)&i, sizeof(int32_t));
	return *this;
}

NzArchive& NzTextArchive::operator << (uint32_t i)
{
    i = htonl(i);
	m_archive.write((const char*)&i, sizeof(uint32_t));
	return *this;
}

NzArchive& NzTextArchive::operator << (int64_t i)
{
    i = htonll(i);
	m_archive.write((const char*)&i, sizeof(int64_t));
	return *this;
}

NzArchive& NzTextArchive::operator << (uint64_t i)
{
    i = htonll(i);
	m_archive.write((const char*)&i, sizeof(uint64_t));
	return *this;
}

NzArchive& NzTextArchive::operator << (double d)
{
	m_archive.write((const char*)&d, sizeof(double));
	return *this;
}

NzArchive& NzTextArchive::operator << (float f)
{
	m_archive.write((const char*)&f, sizeof(float));
	return *this;
}

NzArchive& NzTextArchive::operator << (const char* str)
{
	uint32_t len = strlen(str);
	*this << len;
	m_archive.write(str, len);
	return *this;
}

NzArchive& NzTextArchive::operator << (const std::string& str)
{
    std::string tmp(str);
	uint32_t len = tmp.size();
	*this << len;
	m_archive.write(tmp.c_str(), len);
	return *this;
}

NzArchive& NzTextArchive::operator << (const NzSerializable& se)
{
	*this << se.GetID();
	*this << se.GetVersion();
	se.Serialize(*this);
	return *this;
}

NzArchive& NzTextArchive::operator << (const NzArchive& Archive)
{
	uint32_t len = Archive.str().length();
	*this << len;
	m_archive.write(Archive.str().c_str(), len);
	return *this;
}

NzArchive& NzTextArchive::operator >> (bool& b)
{
	m_archive.read((char*)&b, sizeof(bool));
	return *this;
}
NzArchive& NzTextArchive::operator >> (int8_t& i)
{
	m_archive.read((char*)&i, sizeof(int8_t));
	return *this;
}

NzArchive& NzTextArchive::operator >> (uint8_t& i)
{
	m_archive.read((char*)&i, sizeof(uint8_t));
	return *this;
}

NzArchive& NzTextArchive::operator >> (int16_t& i)
{
	m_archive.read((char*)&i, sizeof(int16_t));
	i = ntohs(i);
	return *this;
}

NzArchive& NzTextArchive::operator >> (uint16_t& i)
{
	m_archive.read((char*)&i, sizeof(uint16_t));
	i = ntohs(i);
	return *this;
}

NzArchive& NzTextArchive::operator >> (int32_t& i)
{
	m_archive.read((char*)&i, sizeof(int32_t));
	i = ntohl(i);
	return *this;
}

NzArchive& NzTextArchive::operator >> (uint32_t& i)
{
	m_archive.read((char*)&i, sizeof(uint32_t));
	i = ntohl(i);
	return *this;
}

NzArchive& NzTextArchive::operator >> (int64_t& i)
{
	m_archive.read((char*)&i, sizeof(int64_t));
	i = ntohll(i);
	return *this;
}

NzArchive& NzTextArchive::operator >> (uint64_t& i)
{
	m_archive.read((char*)&i, sizeof(uint64_t));
	i = ntohll(i);
	return *this;
}


NzArchive& NzTextArchive::operator >> (double& d)
{
	m_archive.read((char*)&d, sizeof(double));
	return *this;
}

NzArchive& NzTextArchive::operator >> (float& f)
{
	m_archive.read((char*)&f, sizeof(float));
	return *this;
}

NzArchive& NzTextArchive::operator >> (char* str)
{
	uint32_t size;
	*this >> size;
	if(str != 0) {
        if(strlen(str) != size)
        {
            delete str;
            str = new char[size];
        }
	}
	m_archive.read(str, size);
	return *this;
}

NzArchive& NzTextArchive::operator >> (std::string& str)
{
	uint32_t size;
	*this >> size;
	char* buffer = new char[size+1];
	m_archive.read(buffer, size);
	buffer[size] = 0;
	str = std::string(buffer);
	delete buffer;
	return *this;
}

NzArchive& NzTextArchive::operator >> (NzSerializable& se)
{
	int32_t id, version;
	*this >> id;
	*this >> version;
	if(id != se.GetID())
	{
	    Util::LogManager::error("Bad class deserialized: expected "+Util::ToString(se.GetID())+" got "+Util::ToString(id));
		return *this;
    }
	if(version != se.GetVersion())
		Util::LogManager::error("Bad version deserialized: expected "+Util::ToString(se.GetVersion())+" got "+Util::ToString(version));

	se.Deserialize(*this);
	return *this;
}

void NzTextArchive::place(nzBuffer type, int pos)
{
	if(type == nzBuffer::nzBuffer_Reader)
		m_archive.seekg(pos, std::ios::beg);
	else if(type == nzBuffer::nzBuffer_Writer)
		m_archive.seekp(pos, std::ios::beg);
}