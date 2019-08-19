#include "KInputManager.h"
#include <Windows.h>

#include <iostream>


void KInputManager::update(const int& _Value)
{
	SHORT X = GetAsyncKeyState(_Value);

	system("cls");
	std::cout << X;
}

bool KInputManager::is_press(const int& _Value)
{
	SHORT X = GetAsyncKeyState(_Value);
	if (0 == X)
	{
		return false;
	}

	return true;
}