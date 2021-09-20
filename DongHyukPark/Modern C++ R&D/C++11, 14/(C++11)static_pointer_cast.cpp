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

std::static_pointer_cast, std::dynamic_pointer_cast 이 두가지는 상속구조에서 사용한다.

static_pointer_cast는 자식 클래스에서 부모클래스로 형변환 할 때 사용하며(UP)
std::dynamic_pointer_cast는 부모 클래스에서 자식 클래스로 형변환 할 때 사양된다(다운)

Reference
https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast

- 참고 사항
Smart Pointer의 Get()을 사용해서도 가능하지만 의도치 않은 동작이 발생할 수 있기 때문에 이 캐스팅을
사용할 것을 권장하고 있다.(동일한 객체를 두 번 삭제할려고 할 수 있음)

*/


#include<iostream>
#include<memory>

class Based {
public:
     void Print()const { std::cout << "I am Based Class" << "\n"; }
};

class Sub : public Based {
public:
    void Print()const  { std::cout << "I am Sub Class" << "\n"; }
};

int main() {

    std::shared_ptr<Sub> sPtrSub = std::make_shared<Sub>();

    sPtrSub->Print(); 

    //static_pointer_cast 캐스팅
    std::shared_ptr<Based> sPtrBase = std::static_pointer_cast<Based>(sPtrSub);
    
    sPtrBase->Print();

    //복사를 하기 때문에 ref Count는 2
    std::cout << sPtrSub.use_count() << "\n";
}