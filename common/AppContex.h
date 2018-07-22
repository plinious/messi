#ifndef MESSI_COMMON_APPCONTEX_H
#define MESSI_COMMON_APPCONTEX_H

#include "types.h"

MESSI_NAMESPACE_START

class AppContex {
    public:
        AppContex() {}
        ~AppContex() {}

    public:
        std::string name_;
        std::string version_;

};

MESSI_NAMESPACE_END

#endif // MESSI_COMMON_APPCONTEX_H
