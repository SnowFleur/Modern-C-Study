/*
요약
- C++17에서는 std::any라는 타입을 지원한다. 이 타입을 가지고 void*을 대체해보자
- 이 std::any는 타입에 대해 더 안전하며 종류에 상관없이 어떤 변수든 자유롭게 확인하고 접근하는 것이 가능해졌다.


설명: 예전에는 void* 포인터를 다양한 객체의 포인터를 저장할 수 있었다. void 타입 포인터만으로는
어떤 객체를 가리키는지 알 수 없었기 때문에 별도의 코드를 직접 작성해 넣었어야 했다.

*/

#include<iostream>
#include<iomanip>
#include<list>
#include<any>
#include<iterator>


using int_list = std::list<int>;
using namespace std;


//어떤 것이든 출력할 수 있는 제네릭한 함수
void PrintAnyThing(const  std::any& a)
{
	if (a.has_value() == false)
	{
		std::cout << "비어있습니다.\n";
		return;
	}

	// 비어있지 않은 경우 일치하는 타입을 발견할 때까지 다양한 타입과 비교를 진행한다.
	// any_cast<>는 복사본을 반환하기 때문에 주의한다.
	try
	{
		if (a.type() == typeid(std::string))
		{
			std::cout << "이 타입은 string입니다. : " << std::quoted(std::any_cast<const std::string&>(a)) << "\n";
		}
		else if (a.type() == typeid(int))
		{
			std::cout << "이 타입은 int입니다.: " << std::any_cast<int>(a) << "\n";
		}
		else if (a.type() == typeid(int_list))
		{
			/*
			std::any는 string이나 int와 같이 간단한 타입 외에도
			전체 맵이나 리스트, 복잡한 데이터 구조체 같은 것들도 any변수에 입력할 수 있다.
			*/

			const auto& l(std::any_cast<const int_list&>(a));

			std::cout << "이 타입은 List입니다.: ";

			std::copy(std::begin(l), std::end(l), std::ostream_iterator<int>{std::cout, ","});
			std::cout << "\n";
		}
		else
		{
			std::cout << "일치하는 항목이 없습니다.\n";
		}
	}
	catch (std::bad_any_cast& cast)
	{
		std::cout << cast.what() << "\n";
	}
}


int main()
{

	PrintAnyThing({});
	PrintAnyThing("abc"s);
	PrintAnyThing(123);
	PrintAnyThing(int_list{ 1,2,3 });

	// any변수에 복사하는 비용이 많이 드는 객체는 내부 생성을 사용해도 된다.
	PrintAnyThing(std::any(std::in_place_type_t<int_list>{}, { 1,2,3 }));

}

