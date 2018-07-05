#ifndef _MESSI_SINGLETON_H_
#define _MESSI_SINGLETON_H_

#include "types.h"

MESSI_NAMESPACE_START

template <class T>
class Singleton {

    protected:
        Singleton() {}
        Singleton(const Singleton &);
        Singleton &operator=(const Singleton &);

    public:
        virtual ~Singleton() {}
        Singleton &getInstance() {}
};

MESSI_NAMESPACE_END

#endif // _MESSI_SINGLETON_H_
