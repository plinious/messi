#ifndef _MESSI_COMPRESS_H

namespace messi {
namespace util {

    enum COMPRESS_LEVEL {

        COM_NONE = 0,       // return the data as itself
        COM_LEVEL_LITE,     // compress a little
        COM_LEVEL_MEDIUM,   // most situation you may want this one
        COM_LEVEL_MUCH,     // very much compressed
        COM_LEVEL_EXTREME,  // the best compressed,lowest in timecost
        COM_LEVEL_END       // illegal
    };

    enum COMPRESS_METHOD {
        COM_ZLIB = 0,
        COM_LZ4,
        COM_SNAPPY,
        COM_ZSTD,
        COM_ZOPFLI,
        COM_BROTLI,
        COM_METHOD_END
    };

    enum COMPRESS_ERROR {
        COM_SUCC = 0,
        COM_METHOD_INVALID,
        COM_DATA_EMPTY,
        COM_DATA_TOO_LARGE,
        COM_LEVEL_INVALID,
        COM_INNER_ERROR
    };

    class CompressWrap {
    public:

        static size_t MAX_SIZE = 1024000;

        static int compressByMethod(const std::string &src,
                std::string &dest,
                COMPRESS_METHOD method = COMPRESS_LZ4,
                size_t compress_level = 3);

        static int decompressByMethod(const std::string &src,
                std::string &dest,
                COMPRESS_METHOD method = COMPRESS_LZ4);
    };

} }

#iendif // _MESSI_COMPRESS_H
