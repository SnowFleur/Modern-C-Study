#pragma once
#include"WindowsHeader.h"

struct STLockGuard
{
public:
    CRITICAL_SECTION& stOwnerLock;
    explicit STLockGuard(CRITICAL_SECTION& lock) :
        stOwnerLock(lock)
    {
        EnterCriticalSection(&stOwnerLock);
    }

    ~STLockGuard()noexcept
    {
        LeaveCriticalSection(&stOwnerLock);
    }

    STLockGuard(STLockGuard&)                      = delete;
    STLockGuard(STLockGuard&&)noexcept             = delete;
    STLockGuard& operator=(const STLockGuard&)     = delete;
    STLockGuard& operator=(STLockGuard&&)noexcept  = delete;
};

