#include"ThreadManager.h"

template<class _Ty>
inline CThreadManager<_Ty>::CThreadManager(int32_t maxRunAbleThreadCount):
    MAX_RUNALBE_THREAD_COUNT(maxRunAbleThreadCount)
{

}

template<class _Ty>
inline CThreadManager<_Ty>::~CThreadManager() noexcept{

}

template<class _Ty>
inline void CThreadManager<_Ty>::AddThread(THREAD_KEY key, _Ty&& thread) {
    mapThreadList_.emplace(THREAD_KEY, std::forward<_Ty>(thread));
}

