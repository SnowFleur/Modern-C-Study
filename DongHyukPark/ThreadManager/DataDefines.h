#pragma once


#define SAFE_DELETE(X)          if(x!=nullptr)delete x;



#ifdef _WIN64
#define THREAD_KEY              uint64_t
#else
#define THREAD_KEY              uint32_t
#endif

