#pragma once
#include<iostream>

#include"Singleton.h"
#include"DataTypes.h"

/*
-   [2021-05-05]
-   CLogCollector
-   Log ��� �� �α� �����? --> Log Server�� ����� �͵� ��� (UDP)
-   ������ ������ ���� ����ó��
*/
class CLogCollector :public CSingleton<CLogCollector> {
private:

public:
#if VER_CPP_17 // c++17�̻�
    template<class... _Args>
    void PrintLog(_Args... args)const {
        ((std::cout << args << " "), ...) << "\n";
    }

#elif VER_CPP_14 || VER_CPP_11  //C++ 14 || C++11
    template<class _Ty, class... _Args>
    void PrintLog(_Ty message, _Args... args)const {
        std::cout << message << " ";
        PrintLog(args...);
    }

    template<class _Ty>
    void PrintLog(_Ty message)const {
        std::cout << message << "\n";
    }
#else
    //ERROR
#endif //  _MSC_VER 

};


/*
- Meesage: ��� ����
*/
#define PRINT_LOG(message,...)          CLogCollector::GetInstance()->PrintLog(message,__VA_ARGS__)
#define PRINT_INFO_LOG(message,...)     CLogCollector::GetInstance()->PrintLog("[INFOR]",message,__VA_ARGS__)
#define PRINT_ERROR_LOG(message,...)    CLogCollector::GetInstance()->PrintLog("[ERROR]",message,__VA_ARGS__)


