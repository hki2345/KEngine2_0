#include "KInputManager.h"
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
	if (0 != X)
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


void KInputManager::release()
{
	RELEASE_PTR(pKInputManager);
}
