#include "Compress.h"

namespace messi {
namespace util {

    int compressByMethod(const std::string &src,
            std::string &dest,
            COMPRESS_METHOD method,
            size_t compress_level) {

        if (src.empty()) {
            return (int)(COM_DATA_EMPTY);
        }
        if (src.size() > MAX_SIZE) {
            return (int)(COM_DATA_TOO_LARGE);
        }
        if (method < 0 || method >= COM_METHOD_END) {
            return (int)(COM_METHOD_INVALID);
        }
        if (compress_level < 0 || compress_level >=10) {
            return (int)(COM_LEVEL_INVALID);
        }
        switch (method) {
            case COM_ZLIB:
                break;
            case COM_LZ4:
                break;
            case COM_SNAPPY:
                break;
            case COM_ZSTD:
                break;
            case COM_ZOPFLI:
            case COM_BROTLI:
                break;
            default:
                break;
        }
    }

    int decompressByMethod(const std::string &src,
            std::string &dest,
            COMPRESS_METHOD method = COMPRESS_LZ4);
} }
