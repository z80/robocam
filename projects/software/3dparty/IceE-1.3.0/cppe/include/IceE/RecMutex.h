// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_RMUTEX_H
#define ICEE_RMUTEX_H

#include <IceE/Config.h>
#include <IceE/Lock.h>
#include <IceE/ThreadException.h>
#include <IceE/MutexProtocol.h>

namespace IceUtil
{

//
// Forward declarations for friend.
//
class Cond;

//
// Recursive Mutex implementation.
//
class ICE_API RecMutex
{
public:

    //
    // Lock & TryLock typedefs.
    //
    typedef LockT<RecMutex> Lock;
    typedef TryLockT<RecMutex> TryLock;

    RecMutex();
    explicit RecMutex(MutexProtocol);
    ~RecMutex();

    //
    // Note that lock/tryLock & unlock in general should not be used
    // directly. Instead use Lock & TryLock.
    //
    
    void lock() const;

    //
    // Returns true if the lock was acquired, and false otherwise.
    //
    bool tryLock() const;

    
    void unlock() const;

    //
    // Returns true if the mutex will unlock when calling unlock()
    // (false otherwise). For non-recursive mutexes, this will always
    // return true. 
    // This function is used by the Monitor implementation to know whether 
    // the Mutex has been locked for the first time, or unlocked for the 
    // last time (that is another thread is able to acquire the mutex).
    // Pre-condition: the mutex must be locked.
    //
    bool willUnlock() const;

private:

    void init(MutexProtocol);

    // noncopyable
    RecMutex(const RecMutex&);
    void operator=(const RecMutex&);

    //
    // LockState and the lock/unlock variations are for use by the
    // Condition variable implementation.
    //
#ifdef _WIN32
    struct LockState
    {
        int count;
    };
#else
    struct LockState
    {
        pthread_mutex_t* mutex;
        int count;
    };
#endif

    void unlock(LockState&) const;
    void lock(LockState&) const;

    friend class Cond;

#ifdef _WIN32
    mutable CRITICAL_SECTION _mutex;
#else
    mutable pthread_mutex_t _mutex;
#endif    

    mutable int _count;
};

} // End namespace Ice

#endif
