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
	HWND handle = NULL; //������ �ڵ�
	HINSTANCE hInstance = NULL; //application instance �ڵ�
	std::string window_title = "";
	std::wstring window_title_wide = L""; //Ÿ��Ʋ
	std::string window_class = "";
	std::wstring window_class_wide = L""; //������
	int width = 0;
	int height = 0;

};

