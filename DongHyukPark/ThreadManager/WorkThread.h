#pragma once

#include"ThreadBase.h"

class CWorkThread :public CThreadBase {
private:

public:
    CWorkThread();
    ~CWorkThread()noexcept;

public:
    void Run()override;

};