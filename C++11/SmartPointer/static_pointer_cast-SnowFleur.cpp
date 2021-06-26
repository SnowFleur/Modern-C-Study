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

이 4가지는 전부 Shared Ptr에서 작동한다. 기본적으로 상속구조에서 사용하는 것으로 보임

static_pointer_cast는 자식 클래스에서 부모클래스로 형변환 할 때 사용하며(UP)
std::dynamic_pointer_cast는 부모 클래스에서 자식 클래스로 형변환 할 때 사양된다(다운)
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