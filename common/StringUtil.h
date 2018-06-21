#ifndef _MESSI_COMMON_STRINGUTIL_H
#define _MESSI_COMMON_STRINGUTIL_H

#include "types.h"
#include "MCResult.h"

MESSI_NAMESPACE_START

class StringUtil {
    public:

        static std::string charToHex(unsigned char ch);
        static std::string toHex(const char *src, size_t len);
        static std::string toHex(const std::string &src);

        static Strings split(const std::string& val, char ch = ' ', uint32_t maxcount = -1);

        template <class T>
        static MCResult<T> toInt(const std::string &val){
            if (val.empty()) {
                return MCResult<T>::getFailureResult("1", "empty");
            }
            return MCResult<T>::getSuccessResult((T)strtoul(val.c_str(), NULL, 10));
        }

        static std::string toString(int64_t val);
        static std::string toString(uint64_t val);
        static std::string toString(int32_t val);
        static std::string toString(uint32_t val);

};

MESSI_NAMESPACE_END

#endif // _MESSI_COMMON_STRINGUTIL_H
