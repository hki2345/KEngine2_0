#include <iostream>
#include <fstream>
#include <map>

#include <sstream>
#include <locale>
#include <vector>
#include <Windows.h>


class AAA
{
	int x;
};

class BBB
{
public:
	BBB() {};
	~BBB() {};

private:

}; 


int main()
{
	AAA a = AAA();

	BBB b1 = BBB();
	BBB b2 = BBB(b1);

	size_t AA = typeid(a).hash_code();


	char orig[64] = "Hello, World!";
	std::cout << orig << " (char *)" << std::endl;
	size_t newsize = strlen(orig) + 1;
	wchar_t * wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);



	wchar_t greeting[100];
	std::wfstream ifs(L"Game_Table.csv", std::ios::in);
	std::vector<std::wstring> TVec;

	std::locale loc("KOR");
	ifs.imbue(loc);


	std::wcout.imbue(std::locale("kor"));
	while (!ifs.eof())
	{
		ifs.getline(greeting, 100);
		TVec.push_back(greeting);

		wchar_t seps[] = L" ,\t\n";
		wchar_t* tok = nullptr;
		wchar_t* ntok = nullptr;

		tok = wcstok_s(greeting, seps, &ntok);

		while(tok != NULL)
		{
			// While there are tokens in "string"
			std::wcout << L"TEST" << tok;

			// Get next token:
			tok = wcstok_s(NULL, seps, &ntok);
		}
		std::wcout << std::endl;
	} 


	std::wcout << std::endl;
	std::wcout << std::endl;
	std::wcout << std::endl;
	std::wcout << "¾Æ´Ï>?";

	ifs.close();
	/*std::wstringstream wss;
	wss << ifs.rdbuf();*/

	std::wstring Tmp = greeting;
	std::wcout << L"greeting file: " << Tmp.c_str();


	while (true)
	{
		std::wcout << std::endl << std::endl;
		SHORT X = GetAsyncKeyState(VK_LBUTTON);
		SHORT XX = 1;

		if (X == XX)
		{
			int a = 0;
		}
		std::wcout << X << std::endl;
	}

	return 0;
}