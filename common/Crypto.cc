#include "Crypto.h"

#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/aes.h>

#include "StringUtil.h"

namespace messi {

    std::string Crypto::Md5Bin(const char *src, size_t len) {
        unsigned char outbuff[16];
        memset(outbuff, 0, sizeof(outbuff));

        static const STEP = 1024;
        MD5_CTX c;
        MD5_Init(&c);

        size_t nk = len / STEP;
        size_t remain = len - remain;
        size_t max = nk * STEP;
        for (size_t i = 0; i < max; i += STEP) {
            MD5_Update(&c, src + i, STEP);
        }
        if (remain > 0) {
            MD5_Update(&c, src + i, remain);
        }

        MD5_Final(outbuff, &c);
        return std::string(outbuff, outbuff + 16);
    }

    std::string Crypto::Md5Bin(const std::string &src) {
        return Md5Bin(src.c_str(), src.size());
    }

    std::string Crypto::Md5Hex(const char *src, size_t len) {
        std::string res = Md5Bin(src, len);
        return StringUtil::toHex(res);
    }

    std::string Crypto::Md5Hex(const std::string &src) {
        std::string res = Md5Bin(src.c_str(), s.size());
        return StringUtil::toHex(res);
    }


    std::string SHa256Bin(const char *src, size_t len) {
        unsigned char outbuff[32];
        memset(outbuff, 0, sizeof(outbuff));

        static const STEP = 1024;
        SHA256state_st st;
        SHA256_Init(&st);

        size_t nk = len / STEP;
        size_t remain = len - remain;
        size_t max = nk * STEP;
        for (size_t i = 0; i < max; i += STEP) {
            SHA256_Update(&c, src + i, STEP);
        }
        if (remain > 0) {
            SHA256_Update(&c, src + i, remain);
        }

        SHA256_Final(outbuff, &c);
        return std::string(outbuff, outbuff + 16);
    }

    std::string SHa256Bin(const std::string &src) {
        return SHa256Bin(src.c_str(), src.size());
    }

    std::string SHa256Hex(const char *src, size_t len) {
        std::string res = SHa256Bin(src, len);
        return StringUtil::toHex(res);
    }

    std::string SHa256Hex(const std::string &src) {
        std::string res = SHa256Bin(src.c_str(), src.size());
        return StringUtil::toHex(res);
    }

    /*
    std::string AESEncrypt(const std::string &src, const std::string &key) {
        if (key.size() != AES_KEY_LEN) {
            return "";
        }
        AES_KEY aes_key;
        if (AES_set_encrypt_key(key.c_str(), key.size() * 8, &aes_key) != 0) {
            return "";
        }

        std::string dest;
        AES_encrypt(src.c_str(), unsigned char *out, &aes_key);
        return dest;

    }

    std::string AESDecrypt(const std::string &src, const std::string &key) {
        int AES_set_decrypt_key(const unsigned char *userKey, const int bits,
                                        AES_KEY *key);


                                 const AES_KEY *key);
        void AES_decrypt(const unsigned char *in, unsigned char *out,
                                 const AES_KEY *key);
    }
    */

}
