#pragma once

#include"DataTypes.h"
#include"DefineUtilty.h"

/*
-   [2021.09.08]
-   SImple Buffer 기능을 가지는 Class
-
*/

class CBuffer {
private:
	const uint32_t        BUFFER_SIZE;

	char*                 buffer_;
    WSABUF                wsaBuf_;
public:

	CBuffer(const uint32_t bufferSize):
		BUFFER_SIZE(bufferSize),
		buffer_(nullptr)
	{
		//어쩔 수 없이 동적할당
		buffer_			= new char[BUFFER_SIZE];
		wsaBuf_.buf		= buffer_;
		wsaBuf_.len		= BUFFER_SIZE;
	}

	~CBuffer()noexcept {
		SAFE_DELETE_MULTI(buffer_);
	}

	LPWSABUF GetWSABuffer() {
		return &wsaBuf_;
	}

	char* GetBuffer()inline const{
		return  buffer_ == nullptr ? nullptr : buffer_;
	}

	uint32_t GetBufferSize()inline const {
		return BUFFER_SIZE;
	}
    
	bool SetBuffer(const char* buffer,const uint32_t setBufferSize)  {
		if (buffer == nullptr) return false;
		if (setBufferSize > BUFFER_SIZE)return false;

		memcpy_s(buffer_, setBufferSize, buffer, setBufferSize);
		return true;
	}
};