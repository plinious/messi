#ifndef _MESSI_COMMON_CRYPTO_H
#define _MESSI_COMMON_CRYPTO_H

#include <string>

namespace messi {
    class Crypto {
        public:

            static std::string Md5Hex(const std::string &src);
            static std::string Md5Hex(const char *src, size_t len);
            static std::string Md5Bin(const std::string &src);
            static std::string Md5Bin(const char *src, size_t len);

            static std::string SHa256Hex(const std::string &src);
            static std::string SHa256Hex(const char *src, size_t len);
            static std::string SHa256Bin(const std::string &src);
            static std::string SHa256Bin(const char *src, size_t len);

            //static std::string AESEncrypt(const std::string &src, const std::string &key);
           // static std::string AESDecrypt(const std::string &src, const std::string &key);

        private:
            static const AES_KEY_LEN = 16;

    };
}

#endif // _MESSI_COMMON_CRYPTO_H
