#ifndef MESSI_COMMON_IPADDR_H
#define MESSI_COMMON_IPADDR_H

#include "types.h"

MESSI_NAMESPACE_START

class IpAddr {
    public:
        IpAddr() : i_(0), type_('N') {}
        explicit IpAddr(const std::string &addr) { setFromString(addr); }
        explicit IpAddr(uint32_t addr) { setFromUint(addr); }
        ~IpAddr() {}

        IpAddr(const IpAddr &r) : s_(r.s_), i_(r.i_) {}
        IpAddr &operator=(const IpAddr &r) {
            if (&r != this) {
                i_ = r.i_;
                s_ = r.s_;
            }
            return *this;
        }

    public:
        bool setFromString(const std::string &s);
        bool setFromUint(uint32_t i);

        bool operator< (const IpAddr &i) { return this->i_ < i.i_; }
        bool operator== (const IpAddr &i) { return this->i_ == i.i_; }
        std::string getIpAddr() { return s_; }
        uint32_t getIpAddrI() { return i_; }
        char getType() { return type_; }

    private:
        char ipType();
        std::string setFromUintImpl(uint32_t i);

    private:
        std::string s_;
        uint32_t    i_;
        char        type_;
};

MESSI_NAMESPACE_END

#endif // MESSI_COMMON_IPADDR_H
