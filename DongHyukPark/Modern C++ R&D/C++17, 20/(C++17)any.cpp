/*
���
- C++17������ std::any��� Ÿ���� �����Ѵ�. �� Ÿ���� ������ void*�� ��ü�غ���
- �� std::any�� Ÿ�Կ� ���� �� �����ϸ� ������ ������� � ������ �����Ӱ� Ȯ���ϰ� �����ϴ� ���� ����������.


����: �������� void* �����͸� �پ��� ��ü�� �����͸� ������ �� �־���. void Ÿ�� �����͸����δ�
� ��ü�� ����Ű���� �� �� ������ ������ ������ �ڵ带 ���� �ۼ��� �־���� �ߴ�.

*/

#include<iostream>
#include<iomanip>
#include<list>
#include<any>
#include<iterator>


using int_list = std::list<int>;
using namespace std;


//� ���̵� ����� �� �ִ� ���׸��� �Լ�
void PrintAnyThing(const  std::any& a)
{
	if (a.has_value() == false)
	{
		std::cout << "����ֽ��ϴ�.\n";
		return;
	}

	// ������� ���� ��� ��ġ�ϴ� Ÿ���� �߰��� ������ �پ��� Ÿ�԰� �񱳸� �����Ѵ�.
	// any_cast<>�� ���纻�� ��ȯ�ϱ� ������ �����Ѵ�.
	try
	{
		if (a.type() == typeid(std::string))
		{
			std::cout << "�� Ÿ���� string�Դϴ�. : " << std::quoted(std::any_cast<const std::string&>(a)) << "\n";
		}
		else if (a.type() == typeid(int))
		{
			std::cout << "�� Ÿ���� int�Դϴ�.: " << std::any_cast<int>(a) << "\n";
		}
		else if (a.type() == typeid(int_list))
		{
			/*
			std::any�� string�̳� int�� ���� ������ Ÿ�� �ܿ���
			��ü ���̳� ����Ʈ, ������ ������ ����ü ���� �͵鵵 any������ �Է��� �� �ִ�.
			*/

			const auto& l(std::any_cast<const int_list&>(a));

			std::cout << "�� Ÿ���� List�Դϴ�.: ";

			std::copy(std::begin(l), std::end(l), std::ostream_iterator<int>{std::cout, ","});
			std::cout << "\n";
		}
		else
		{
			std::cout << "��ġ�ϴ� �׸��� �����ϴ�.\n";
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

	// any������ �����ϴ� ����� ���� ��� ��ü�� ���� ������ ����ص� �ȴ�.
	PrintAnyThing(std::any(std::in_place_type_t<int_list>{}, { 1,2,3 }));

}

