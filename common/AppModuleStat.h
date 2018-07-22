#ifndef MESSI_COMMON_APPMODULESTAT_H
#define MESSI_COMMON_APPMODULESTAT_H

#include "types.h"

MESSI_NAMESPACE_START

class AppModuleStat {
    public:
        AppModuleStat() {}
        ~AppModuleStat() {}

        std::string toString() {
            return stat_;
        }

        void setStat(const std::string &stat) {
            stat_ = stat;
        }
    private:
        std::string stat_;
};

MESSI_NAMESPACE_END

#endif // MESSI_COMMON_APPMODULESTAT_H
