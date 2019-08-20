#include "KTimeManager.h"
#include <iostream>


int main()
{
	KTimeManager::init();
	while (true)
	{
		KTimeManager::update();
		//system("cls");
		std::cout << KTimeManager::accumulate() << std::endl;
		std::cout << KTimeManager::deltatime() << std::endl;
		std::cout << KTimeManager::fps() << std::endl;
	}
}