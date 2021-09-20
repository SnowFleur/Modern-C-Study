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

Reference
https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast


- ���� ����
Smart Pointer�� Get()�� ����ؼ��� ���������� �ǵ�ġ ���� ������ �߻��� �� �ֱ� ������ �� ĳ������ 
����� ���� �����ϰ� �ִ�.(������ ��ü�� �� �� �����ҷ��� �� �� ����)

*/

#include<iostream>
#include<memory>


int main() {

    std::shared_ptr<int> sIntptr = std::make_shared<int>(0xff);

    printf("%d \n", *sIntptr);

    //reinterpret_pointer_cast�� ĳ����
    std::shared_ptr<char> scharPtr = std::reinterpret_pointer_cast<char>(sIntptr);

    printf("%d \n", *scharPtr);

}