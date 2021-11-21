#pragma once
#include"WindowsHeader.h"

struct stLockGuard
{
public:
    CRITICAL_SECTION& stOwnerLock;
    explicit stLockGuard(CRITICAL_SECTION& lock) :
        stOwnerLock(lock)
    {
        EnterCriticalSection(&stOwnerLock);
    }

    ~stLockGuard()noexcept
    {
        LeaveCriticalSection(&stOwnerLock);
    }

    stLockGuard(stLockGuard&)                      = delete;
    stLockGuard(stLockGuard&&)noexcept             = delete;
    stLockGuard& operator=(const stLockGuard&)     = delete;
    stLockGuard& operator=(stLockGuard&&)noexcept  = delete;
};

