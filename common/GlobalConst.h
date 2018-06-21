#ifndef MESSI_COMMON_GLOBALCONST_H
#define MESSI_COMMON_GLOBALCONST_H

#include <string>

namespace messi {

class GlobalConst {
public:
    static const std::string _s_empty;
    static const std::string _s_zero;
    static const std::string _s_one;
    static const std::string _s_two;

    static const char hex[17];
    static const char alpha[27];
    static const char alnum[37];
    static const char visiable[61];
};

}
#endif // MESSI_COMMON_GLOBALCONST_H
