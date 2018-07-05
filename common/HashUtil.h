#ifndef _MESSI_COMMON_HASH_UTIL_H
#define _MESSI_COMMON_HASH_UTIL_H

#include<string>

namespace messi {

    class HashUtil {
        public:

            template <T>
            static T BKDRfunc(const std::string &s) {
                T seed = 131;
                T sum = 0;
                for (size_t i = 0; i < s.size(); ++i) {
                    sum += (seed * sum) + static_cast<uint8_t>(s[i]);
                }
                return sum;
            }

            static int32_t BKDRHash(const std::string &s) {
                return BKDRHash<int32_t>(s);
            }

            static int32_t CRC16(const std::string &s);
            static int32_t CRC32(const std::string &s);

    };
}

#endif // _MESSI_COMMON_HASH_UTIL_H
