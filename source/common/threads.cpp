#include "common/runtime.h"
#include "common/threads.h"

using namespace love;

/* MUTEX */

Mutex::Mutex()
{
    this->mutex = SDL_CreateMutex();
}

Mutex::~Mutex()
{
    SDL_DestroyMutex(this->mutex);
}

void Mutex::lock()
{
    SDL_LockMutex(this->mutex);
}

void Mutex::unlock()
{
    SDL_UnlockMutex(this->mutex);
}

/* LOCKS */

Lock::Lock(Mutex * m)
    : mutex(m)
{
    mutex->lock();
}

Lock::Lock(Mutex & m)
    : mutex(&m)
{
    mutex->lock();
}

Lock::Lock(Lock && other)
{
    mutex = other.mutex;
    other.mutex = nullptr;
}

Lock::~Lock()
{
    if (mutex)
        mutex->unlock();
}

/* MUTEX REF */

MutexRef::MutexRef() : mutex(new Mutex())
{
}

MutexRef::~MutexRef()
{
    delete mutex;
}

MutexRef::operator Mutex*() const
{
    return mutex;
}

Mutex *MutexRef::operator->() const
{
    return mutex;
}
