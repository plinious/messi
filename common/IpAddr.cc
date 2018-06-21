#include "IpAddr.h"

#include "StringUtil.h"

#include "MCResult.h"

MESSI_NAMESPACE_START

const static uint32_t TYPE_A_START = 0u;
const static uint32_t TYPE_B_START = 2147483648u;   // 128.0.0.0
const static uint32_t TYPE_C_START = 3221225472u;   // 192.0.0.0
const static uint32_t TYPE_D_START = 3758096384u;   // 224.0.0.0
const static uint32_t TYPE_E_START = 4026531840u;   // 240.0.0.0
const static uint32_t TYPE_E_END   = 4160749567u;   // 247.255.255.255

bool IpAddr::setFromString(const std::string &s) {
    Strings svec = StringUtil::split(s, '.');
    if (svec.size() != 4) {
        return false;
    }
    uint32_t iresult = 0;
    for (size_t i = 0 ; i < svec.size(); ++i) {
        MCResult<uint32_t> iRs = StringUtil::toInt<uint32_t>(svec[i]);
        if (!iRs.isSuccess()) {
            return false;
        }
        if (iRs.getResult() >= 256u) {
            return false;
        }
        iresult += (iRs.getResult() << (24 - 8 * i));
    }
    i_ = iresult;
    s_ = setFromUint(i_);
    type_ = ipType();
    return type_ != 'N';
}

bool IpAddr::setFromUint(uint32_t i) {
    i_ = i;
    s_ = setFromUintImpl(i);
    type_ = ipType();
    return type_ != 'N';
}

char IpAddr::ipType() {
    if (i_ < TYPE_B_START) {
        return 'A';
    }
    if (i_ < TYPE_C_START) {
        return 'B';
    }
    if (i_ < TYPE_D_START) {
        return 'C';
    }
    if (i_ < TYPE_E_START) {
        return 'D';
    }
    if (i_ <= TYPE_E_END) {
        return 'E';
    }
    return 'N';
}

std::string IpAddr::setFromUintImpl(uint32_t i) {
    std::string s;
    s.reserve(32);
    s.append(StringUtil::toString((i >> 24) & 0xFF).append(1, '.'));
    s.append(StringUtil::toString((i >> 16) & 0xFF).append(1, '.'));
    s.append(StringUtil::toString((i >> 8) & 0xFF).append(1, '.'));
    s.append(StringUtil::toString(i & 0xFF));
    return s;
}

MESSI_NAMESPACE_END
