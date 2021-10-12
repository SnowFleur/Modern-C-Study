#pragma once

/*
- [2021.06.12]
-  싱글턴을 사용할 클래스가 상속받는 싱글턴 Class
-
-
*/

template<class _Ty>
class CSingleton
{
private:
    static _Ty* instance_;
protected:
    CSingleton() = default;
public:
    virtual ~CSingleton() {}

    static _Ty* GetInstance() 
    {

        if (instance_ == nullptr) {
            instance_ = new _Ty();
        }
        return instance_;
    }

    static void Release()
    {
        if (instance_ != nullptr) {
            delete instance_;
            instance_ = nullptr;
        }
    }

};


template<class _Ty>
_Ty* CSingleton<_Ty>::instance_ = nullptr;

