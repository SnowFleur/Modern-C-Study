/*
- Compiler Ver: C++17
- IDE: Visual Studio 2019
- Developer: SnowFleur
*/


/*
스마트 포인터의 캐스팅은 4가지가 있다.

std::static_pointer_cast
std::dynamic_pointer_cast
std::const_pointer_cast
std::reinterpret_pointer_cast(C++17 부터)

이 4가지는 전부 Shared Ptr에서 작동한다.

Reference
https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast


- 참고 사항
Smart Pointer의 Get()을 사용해서도 가능하지만 의도치 않은 동작이 발생할 수 있기 때문에 이 캐스팅을 
사용할 것을 권장하고 있다.(동일한 객체를 두 번 삭제할려고 할 수 있음)

*/

#include<iostream>
#include<memory>


int main() {

    std::shared_ptr<int> sIntptr = std::make_shared<int>(0xff);

    printf("%d \n", *sIntptr);

    //reinterpret_pointer_cast로 캐스팅
    std::shared_ptr<char> scharPtr = std::reinterpret_pointer_cast<char>(sIntptr);

    printf("%d \n", *scharPtr);

}