#include "StringUtil.h"

#include <iostream>

using namespace std;

MESSI_NAMESPACE_START

std::string StringUtil::charToHex(unsigned char ch) {
    unsigned char high = ((ch >> 4) & 0x0f);
    unsigned char low  = (ch & 0x0f);
    std::string s;
    s.append(1, GlobalConst::hex[high]);
    s.append(1, GlobalConst::hex[low]);
    return s;
}

std::string StringUtil::toHex(const char *src, size_t len) {
    std::string res;
    for (size_t i = 0; i < len; ++i) {
        res.append(charToHex(src[i]));
    }
    return res;
}

std::string StringUtil::toHex(const std::string &src) {
    return toHex(src.c_str(), src.size());
}

Strings StringUtil::split(const std::string& val, char ch/* = ' '*/, uint32_t maxcount/* = -1*/){
    Strings outVals;
    if (val.empty()) {
        return outVals;
    }

    const char* s = val.c_str();
    size_t i = 0;
    size_t j = 0;
    size_t len = val.size();

    while((maxcount -- > 0) && (j < len)) {
        for(; j < len; j ++) {
            if (s[j] == ch) {
                outVals.push_back(std::string(s + i, j - i));
                i = j = j + 1;
                break;
            }
        }
    }

    if (i == 0) {
        outVals.push_back(val);
    } else if (i < len) {
        outVals.push_back(std::string(s + i, len - i));
    }

    return outVals;
}

std::string StringUtil::toString(int64_t val){
    char buf[128];

    int n = snprintf(buf, sizeof(buf)-1, "%lld", val);
    if (n == -1) {
        return "";
    }
    return std::string(buf, n);
}


std::string StringUtil::toString(uint64_t val){
    char buf[128];

    int n = snprintf(buf, sizeof(buf)-1, "%llu", val);
    if (n == -1) {
        return "";
    }
    return std::string(buf, n);
}

std::string StringUtil::toString(int32_t val) {
    return toString((int64_t)val);
}

std::string StringUtil::toString(uint32_t val) {
    return toString((uint64_t)val);
}

MESSI_NAMESPACE_END
