#pragma once
#include<memory>
#include<array>
#include<algorithm>
#include"DataTypes.h"
#include"DefineUtilty.h"

/*
-   [2021.09.08]
-   SImple Buffer 기능을 가지는 Class
-   고정 Array만
*/
constexpr uint32_t                BUFFER_SIZE = 1024;

template<class _Ty>
class CBuffer {
private:
    char          arrBuffer_[BUFFER_SIZE];
    WSABUF        wsaBuf_;
public:

    CBuffer() :
        arrBuffer_{}
    {
        wsaBuf_.buf = arrBuffer_;
        wsaBuf_.len = BUFFER_SIZE;
    }

    ~CBuffer()noexcept {
        ZeroMemory(&wsaBuf_, sizeof(WSABUF));   // 혹시 모르니 내용 Clear
        ZeroMemory(arrBuffer_, BUFFER_SIZE);    // 초기화
    }

    LPWSABUF GetWSABuffer()                { return &wsaBuf_; }
    char* GetBuffer()                      { return arrBuffer_; }
    uint32_t GetBufferSize()inline const   {return BUFFER_SIZE; }

    bool SetBuffer(const char* buffer, const uint32_t setBufferSize) {
        if (buffer == nullptr) return false;
        if (setBufferSize > BUFFER_SIZE)return false;

        memcpy_s(arrBuffer_, BUFFER_SIZE, buffer, setBufferSize);
        return true;
    }
};