#include"JobQueue.h"

template<class _Ty>
inline void CJobQueue<_Ty>::Dequeue(){

}

template<class _Ty>
inline void CJobQueue<_Ty>::EnQueue(_Ty&& ioJob){
    queIoList_.emplace(std::forward<_Ty>(ioJob));
}
