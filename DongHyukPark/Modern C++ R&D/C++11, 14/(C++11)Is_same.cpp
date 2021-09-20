/*
*  IDE:             VS2019
*  Standard:        C++14
*  Description:     C++11���� �����ϴ� ǥ���Լ��� std::is_same�� �����ϰ� ����غ���.
*  More:            �ڷ����� ������ üũ�� �� ����ϸ� ���ƺ���(����ó��)
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