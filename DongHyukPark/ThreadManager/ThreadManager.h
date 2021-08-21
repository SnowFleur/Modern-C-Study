#pragma once

/*
- Thread Manager
*/

#include<vector>
#include"SnowThread.h"
#include"DataDefines.h"

template<class _Ty>
class CThreadManager {
private:
    const uint32_t          MAX_RUNALBE_THREAD_COUNT;
private:
public:
    std::vector<_Ty>        vecThreadList;

    CThreadManager(int32_t  maxRunAbleThreadCount);
    ~CThreadManager()noexcept;

    void AddThread(THREAD_KEY key, _Ty&& thread);
    void AddThread(_Ty&& thread);
    void JoinThread();
};

#include"ThreadManager.inl"

#define ADD_THREAD
#define DISPATCH_THREAD
#define REMOVE_THREAD
#define SUSPEND_THREADD
