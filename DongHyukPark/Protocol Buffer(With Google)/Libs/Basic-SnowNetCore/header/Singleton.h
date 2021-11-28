#pragma once

/*
- Developer: PDH
- Descriptor: ╫л╠шео
*/

template<class _Ty>
class CSingleton
{
private:
    static _Ty* pInstance_;
protected:
    CSingleton() = default;
public:
    virtual ~CSingleton() {}

    static _Ty* GetInstance() 
    {

        if (pInstance_ == nullptr)
        {
            pInstance_ = new _Ty();
        }
        return pInstance_;
    }

    static void Release()
    {
        if (pInstance_ != nullptr)
        {
            delete pInstance_;
            pInstance_ = nullptr;
        }
    }

};


template<class _Ty>
_Ty* CSingleton<_Ty>::pInstance_ = nullptr;

