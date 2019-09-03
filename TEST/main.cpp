#include <iostream>
#include <fstream>
#include <map>

#include <sstream>
#include <locale>
#include <vector>

int main()
{

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
			std::wcout << tok;

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
	return 0;
}