#ifndef MESSI_COMMON_MUTEX_LOCK_H
#define MESSI_COMMON_MUTEX_LOCK_H

#include "Mutex.h"

namespace messi {

    class MutexLock {

    public:
        explicit MutexLock(Mutex &m) : mutex_(m) { mutex_.lock(); }

        ~MutexLock() { mutex_.unLock(); }

    private:
        MutexLock(const MutexLock &);
        MutexLock &operator=(const MutexLock &);

    private:
        Mutex mutex_;
    };

    class RLock {
    public:
        explicit RLock(RWMutex &m) : mutex_(m) { mutex_.rdLock(); }
        ~RLock() { mutex_.unlock(); }

    private:
        RLock(const RLock &);
        RLock &operator=(const RLock &);

    private:
        RWMutex mutex_;
    };

    class WLock {
    public:
        explicit WLock(RWMutex &m) : mutex_(m) { mutex_.wrLock(); }
        ~WLock() { mutex_.unlock(); }

    private:
        WLock(const WLock &);
        WLock &operator=(const WLock &);

    private:
        RWMutex mutex_;
    };
}

#endif // MESSI_COMMON_MUTEX_LOCK_H
