#include "IConvExt.h"

namespace messi {

bool IConver::convert(const std::string &in, std::string &out) {
    return convertRaw(in.c_str(), in.size(), out);
}

bool IConver::convertRaw(const char *in, size_t inlen, std::string &out) {
        if (in == NULL || inlen <= 0) {
            return false;
        }
        std::string outStr;
        outStr.resize(inlen * 2);
        const char *outPtr = &(outStr[0]);
        size_t outSizeTotal = outStr.size();
        size_t outSize = outSizeTotal;
        
        while (inlen > 0) {
            size_t ret = iconv(convertor_, &in, &inlen, &outPtr, &outSize);
            if (ret == (size_t)(-1)) {
                return false;
            }
        }
        out.resize(outSizeTotal - outSize);
        return true;
}

}
