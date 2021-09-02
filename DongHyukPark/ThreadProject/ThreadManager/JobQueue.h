#pragma once

#include<queue>
#include"Lock.h"


template<class _Ty>
class CJobQueue {
private:
    std::queue<_Ty>     queIoList_;
    Lock                stLock_;
public:
    void Dequeue();
    void EnQueue(_Ty&& ioJob);

};

#include"JobQueu.inl"