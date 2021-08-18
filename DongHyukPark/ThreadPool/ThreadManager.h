#pragma once

/*
- Thread ManagerÀÇ ¿ªÇÒ
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

};

#include"ThreadManager.inl"
