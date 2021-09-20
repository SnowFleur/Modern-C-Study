/*
- Compiler Ver: C++17
- IDE: Visual Studio 2019
- Developer: SnowFleur
*/


/*
����Ʈ �������� ĳ������ 4������ �ִ�.

std::static_pointer_cast
std::dynamic_pointer_cast
std::const_pointer_cast
std::reinterpret_pointer_cast(C++17 ����)

�� 4������ ���� Shared Ptr���� �۵��Ѵ�.

std::static_pointer_cast, std::dynamic_pointer_cast �� �ΰ����� ��ӱ������� ����Ѵ�.

static_pointer_cast�� �ڽ� Ŭ�������� �θ�Ŭ������ ����ȯ �� �� ����ϸ�(UP)
std::dynamic_pointer_cast�� �θ� Ŭ�������� �ڽ� Ŭ������ ����ȯ �� �� ���ȴ�(�ٿ�)

Reference
https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast

- ���� ����
Smart Pointer�� Get()�� ����ؼ��� ���������� �ǵ�ġ ���� ������ �߻��� �� �ֱ� ������ �� ĳ������
����� ���� �����ϰ� �ִ�.(������ ��ü�� �� �� �����ҷ��� �� �� ����)

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

    //static_pointer_cast ĳ����
    std::shared_ptr<Based> sPtrBase = std::static_pointer_cast<Based>(sPtrSub);
    
    sPtrBase->Print();

    //���縦 �ϱ� ������ ref Count�� 2
    std::cout << sPtrSub.use_count() << "\n";
}