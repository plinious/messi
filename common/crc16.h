#ifndef MESSI_COMMON_CRC16_H
#define MESSI_COMMON_CRC16_H

#include <string>

namespace messi {

	class CRC16 {
	public:
		static uint16_t checksum(const void* data, size_t len);
		static uint16_t checksum(const std::string &src) { return checksum(src.c_str(), src.size()); }

	private:
		CRC16();
		CRC16(const CRC16 &);
	};
}

#endif // MESSI_COMMON_CRC16_H




