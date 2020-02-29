#pragma once

#include <SDL.h>

namespace love
{
    class Mutex
    {
        public:
            Mutex();
            ~Mutex();

            void lock();
            void unlock();

        private:
            SDL_mutex * mutex;
            Mutex(const Mutex &) {}
    };

    class Lock
    {
        public:
            Lock(Mutex * m);
            Lock(Mutex & m);
            Lock(Lock && other);
            ~Lock();

        private:
            Mutex * mutex;
    };

    class MutexRef
    {
        public:
            MutexRef();
            ~MutexRef();

            operator Mutex*() const;
            Mutex *operator->() const;

        private:
            Mutex * mutex;
    };
}
