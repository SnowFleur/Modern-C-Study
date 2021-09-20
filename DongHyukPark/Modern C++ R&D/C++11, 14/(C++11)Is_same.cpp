/*
*  IDE:             VS2019
*  Standard:        C++14
*  Description:     C++11에서 지원하는 표준함수인 std::is_same을 간단하게 사용해본다.
*  More:            자료형이 같은지 체크할 때 사용하면 좋아보임(예외처리)
*  Reference:       https://en.cppreference.com/w/cpp/types/is_same
*/

#include<iostream>

class A {
    int a;
};

class B {
    int b;
};

class C {
    int c;
};

class D :C {
    int b;
};


int main() {

   
    std::cout << "Is Same?: " << std::boolalpha << std::is_same<int, int32_t>::value << "\n";   //True
    std::cout << "Is Same?: " << std::boolalpha << std::is_same<int, uint32_t>::value << "\n";  //false
    std::cout << "=====================================================================================\n";
    
    std::cout << "Is Same?: " << std::boolalpha << std::is_same<A, A>::value << "\n";           //True
    std::cout << "Is Same?: " << std::boolalpha << std::is_same<A, B>::value << "\n";           //false
    std::cout << "=====================================================================================\n";

    std::cout << "Is Same?: " << std::boolalpha << std::is_same<C, D>::value << "\n";           //false


}