#include <iostream>
#include <map>





int main()
{
	std::map<int, int>::iterator Iter;


	wchar_t ABC[32] = { L"asdafd" };
	wchar_t DEF[32] = { L"asdfafd" };

	int A = wcscmp(ABC, DEF);

	return 0;
}