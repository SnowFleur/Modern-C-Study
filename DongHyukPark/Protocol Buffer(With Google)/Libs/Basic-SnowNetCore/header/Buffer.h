#pragma once
#include<memory>
#include"DataTypes.h"
#include"DefineUtilty.h"

/*
-   [2021.09.08]
-   SImple Buffer 기능을 가지는 Class
-
*/

template<class _Ty>
class CBuffer {
private:
    const uint32_t             BUFFER_SIZE;
    std::shared_ptr<_Ty[]>     buffer_;
    WSABUF                     wsaBuf_;
public:

	CBuffer(const uint32_t bufferSize):
		BUFFER_SIZE(bufferSize),
		buffer_(nullptr)
	{
		//어쩔 수 없이 동적할당
		buffer_ = std::make_unique<_Ty[]>(BUFFER_SIZE);
		wsaBuf_.buf		= buffer_.get();
		wsaBuf_.len		= BUFFER_SIZE;
	}

    ~CBuffer()noexcept {
        ZeroMemory(&wsaBuf_, sizeof(WSABUF));
        //SAFE_DELETE_MULTI(buffer_); Smart Pointer로 변경
    }


	LPWSABUF GetWSABuffer() {
		return &wsaBuf_;
    }

    std::shared_ptr<_Ty[]> GetBuffer()inline const{
        return  buffer_ == nullptr ? nullptr : buffer_;
    }

	uint32_t GetBufferSize()inline const {
		return BUFFER_SIZE;
	}
    
    bool SetBuffer(const char* buffer, const uint32_t setBufferSize) {
        if (buffer == nullptr) return false;
        if (setBufferSize > BUFFER_SIZE)return false;

        memcpy_s(buffer_.get(), setBufferSize, buffer, setBufferSize);
        return true;
    }
};