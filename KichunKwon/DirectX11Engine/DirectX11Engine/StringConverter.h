#pragma once
#include <string>

class StringConverter
{
public:
	StringConverter() = default;
	~StringConverter() = default;
	static std::wstring StringToWide(std::string str);

private:

};