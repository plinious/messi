#ifndef MESSI_COMMON_MUTEX_H
#define MESSI_COMMON_MUTEX_H

#include <pthread.h>

namespace messi {

    class Mutex {
    public:
        Mutex() { pthread_mutex_init(&mutex_, NULL); }

        ~Mutex() { pthread_mutex_destroy(&mutex_); }

        void lock() { pthread_mutex_lock(&mutex_); }

        void tryLock() { pthread_mutex_trylock(&mutex_); }

        void unLock() { pthread_mutex_unlock(&mutex_); }

    private:
        Mutex(const Mutex &);
        Mutex &operator=(const Mutex &);

    private:
        pthread_mutex_t mutex_;
    };

    class RWMutex {
    public:
        RWMutex() { pthread_rwlock_init(&rwmutex_, NULL); }

        ~RWMutex() { pthread_rwlock_destroy(&rwmutex_); }

        void rdLock() { pthread_rwlock_rdlock(&rwmutex_); }

        void tryRdLock() { pthread_rwlock_tryrdlock(&rwmutex_); }

        void wrLock() { pthread_rwlock_wrlock(&rwmutex_); }

        void tryWrLock() { pthread_rwlock_trywrlock(&rwmutex_); }

        void unLock() { pthread_rwlock_unlock(&rwmutex_); }

    private:
        RWMutex(const RWMutex &);
        RWMutex &operator=(const RWMutex &);

    private:
        pthread_rwlock_t rwmutex_;
    };
}

#endif // MESSI_COMMON_MUTEX_H
