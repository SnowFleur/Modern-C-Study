#pragma once

/*
- Thread Manager
*/

#include<vector>
#include"ThreadBase.h"
#include"DataDefines.h"

template<class _Ty>
class CThreadManager {
private:
    const uint32_t          MAX_RUNALBE_THREAD_COUNT;
private:
    std::vector<_Ty>        vecThreadList;
public:

    CThreadManager(int32_t  maxRunAbleThreadCount);
    ~CThreadManager()noexcept;

    void AddThread(THREAD_KEY key, _Ty&& thread);
};

#include"ThreadManager.inl"

#define ADD_THREAD
#define DISPATCH_THREAD
#define REMOVE_THREAD
#define SUSPEND_THREADD
