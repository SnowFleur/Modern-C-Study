#pragma once

/*
- Thread Manager
*/

#include<map>
#include"ThreadBase.h"
#include"DataDefines.h"

template<class _Ty>
class CThreadManager {
private:
    std::map<THREAD_KEY, _Ty>       mapThreadList_;
public:

    CThreadManager(int32_t  maxThreadCount);
    ~CThreadManager()noexcept;

    void AddThread(THREAD_KEY key, _Ty thread);

};

#include"ThreadManager.inl"


#define ADD_THREAD
#define DISPATCH_THREAD
#define REMOVE_THREAD
#define SUSPEND_THREADD
