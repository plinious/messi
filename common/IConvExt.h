#ifndef _MESSI_COMMON_ICONV_EXT_H
#define _MESSI_COMMON_ICONV_EXT_H

#include <iconv.h>
#include <string>

namespace messi {
    class IConver {
        public:
            IConver(const std::string &from, const std::string &to) {
                iconv_open(from.c_str(), to.c_str());
            }

            ~IConver() {
                iconv_close(convertor_);
            }

            bool convert(const std::string &in, std::string &out);
            bool convertRaw(const char *in, size_t inlen, std::string &out);

        private:
            iconv_t convertor_;
    };


    bool utf8_2_gb18030(const std::string &in, std::string &out) {
        IConver iconv("utf-8", "gb18030//IGNORE");
        return iconv.convert(in, out);
    }

    bool gb18030_2_utf8(const std::string &in, std::string &out) {
        IConver iconv("gb18030//IGNORE", "utf-8");
        return iconv.convert(in, out);
    }

    bool utf8_2_gb18030(const char *in, size_t inlen, std::string &out) {
        if (in == NULL || inlen <= 0) {
            return false;
        }
        IConver iconv("utf-8", "gb18030//IGNORE");
        return iconv.convertRaw(in, inlen, out);
    }

    bool gb18030_2_utf8(const char *in, size_t inlen, std::string &out) {
        if (in == NULL || inlen <= 0) {
            return false;
        }
        IConver iconv("gb18030//IGNORE", "utf-8");
        return iconv.convertRaw(in, inlen, out);
    }

}

#endif // _MESSI_COMMON_ICONV_EXT_H
