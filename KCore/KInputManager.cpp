#include "KInputManager.h"
#include "KWindowManager.h"

#include <Windows.h>

#include <iostream>


KInputManager* KInputManager::pKInputManager = nullptr;




bool KInputManager::is_down(const int& _Value)
{
	SHORT X = GetAsyncKeyState(_Value);
	if (-32767 == X)
	{
		return true;
	}

	return false;
}

bool KInputManager::is_press(const int& _Value)
{
	SHORT X = GetAsyncKeyState(_Value);
	if (-32768 == X || -32767 == X)
	{
		return true;
	}

	return false;
}

bool KInputManager::is_up(const int& _Value)
{
	SHORT X = GetAsyncKeyState(_Value);
	if (1 == X)
	{
		return true;
	}

	return false;
}

bool KInputManager::is_unpress(const int& _Value)
{
	SHORT X = GetAsyncKeyState(_Value);
	if (0 == X)
	{
		return true;
	}

	return false;
}

KPos2 KInputManager::pos_mouse()
{
	POINT pt;
	KPos2 Tmp;
	GetCursorPos(&pt);

	ScreenToClient(KWindowManager::instance()->main_hwnd(), &pt);


	Tmp = pt;
	return Tmp;
}


void KInputManager::release()
{
	RELEASE_PTR(pKInputManager);
}
