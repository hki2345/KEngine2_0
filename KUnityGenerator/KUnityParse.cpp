#include "KUnityParse.h"
#include <iostream>


#include <KPathManager.h>
#include <io.h>



KUnityParse* KUnityParse::pKParse = nullptr;


#if _DEBUG
#if Win32
#pragma comment(lib, "KContainer_Debug32")
#elif x64
#pragma comment(lib, "KContainer_Debug64")
#endif // WIN32

#else
#if Win32
#pragma comment(lib, "KContainer_Release32")
#elif x64
#pragma comment(lib, "KContainer_Release64")
#endif
#endif


KUnityParse::KUnityParse()
{
}


KUnityParse::~KUnityParse()
{
}


void KUnityParse::init()
{
	KPathManager::instance()->init();
	load_cpp();
	save_cpp();
}

void KUnityParse::loop()
{

}



void KUnityParse::update()
{

}



void KUnityParse::load_cpp()
{
	std::wcout << "Load Target To... " << std::endl;
	std::wcin >> sTarget;
	std::wstring TargetPath = KPathManager::instance()->directory();

	TargetPath += sTarget;
	TargetPath += L'\\';
	
	
	struct _wfinddata_t FD;
	intptr_t Handle;

	TargetPath += L"*.*";

	Handle = _wfindfirst(TargetPath.c_str(), &FD);


	while (0 == _wfindnext(Handle, &FD))
	{
		std::wstring Tmp = FD.name;
		if (-1 != (int)Tmp.find(L".cpp"))
		{
			MapCpp.insert(Tmp);
		}
	}

	_findclose(Handle);
}


void KUnityParse::save_cpp()
{
	std::wcout << "Save Target To... " << std::endl;
	std::wcin >> sTarget;
	std::wstring TargetPath = KPathManager::instance()->directory();

	TargetPath += sTarget;
	TargetPath += L'\\';
	sTarget += L".cpp";
	TargetPath += sTarget;

	FILE* NFile;
	_wfopen_s(&NFile, TargetPath.c_str(), L"wt");


	std::multiset<std::wstring>::iterator SIter = MapCpp.begin();
	std::multiset<std::wstring>::iterator EIter = MapCpp.end();


	for (; SIter != EIter; ++SIter)
	{
		std::wstring IncludePath = L"#include <";
		IncludePath += SIter->c_str();
		IncludePath += L">\n" ;

		fwprintf_s(NFile, IncludePath.c_str(), IncludePath.capacity());
	}

	fclose(NFile);
}