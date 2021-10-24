#pragma once
/*
- Developer: SnowFleur
- Descriptor:  SingleTon Class
*/

template<class _Ty>
class CSingleton {
private:
    static _Ty* instance_;
protected:
    CSingleton() = default;
public:
    virtual ~CSingleton() {}

    static _Ty* GetInstance() {

        if (instance_ == nullptr) {
            instance_ = new _Ty();
        }
        return instance_;
    }

    static void Release() {
        if (instance_ != nullptr) {
            delete instance_;
            instance_ = nullptr;
        }
    }

};


template<class _Ty>
_Ty* CSingleton<_Ty>::instance_ = nullptr;

