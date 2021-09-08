#pragma once
#include "ErrorLogger.h"

class WindowContainer;

class RenderWindow
{
public:
	bool Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	~RenderWindow();
private:
	void RegisterWindowClass();
	HWND handle = NULL; //윈도우 핸들
	HINSTANCE hInstance = NULL; //application instance 핸들
	std::string window_title = "";
	std::wstring window_title_wide = L""; //타이틀
	std::string window_class = "";
	std::wstring window_class_wide = L""; //윈도우
	int width = 0;
	int height = 0;

};

