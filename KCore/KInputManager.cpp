#include "KInputManager.h"
#include <Windows.h>

#include <iostream>


KInputManager* KInputManager::pKInputManager = nullptr;


void KInputManager::update(const int& _Value)
{
	SHORT X = GetAsyncKeyState(_Value);
	std::cout << X;
}

void KInputManager::release()
{
	RELEASE_PTR(pKInputManager);
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