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
	std::cin >> sTarget;
	std::string TargetPath = KPathManager::instance()->directory();

	TargetPath += sTarget;
	TargetPath += '\\';
	
	
	struct _finddata_t FD;
	intptr_t Handle;

	TargetPath += "*.*";

	Handle = _findfirst(TargetPath.c_str(), &FD);


	while (0 == _findnext(Handle, &FD))
	{
		std::string Tmp = FD.name;
		if (-1 != (int)Tmp.find(".cpp"))
		{
			MapCpp.insert(Tmp);
		}
	}

	_findclose(Handle);
}


void KUnityParse::save_cpp()
{
	std::cin >> sTarget;
	std::string TargetPath = KPathManager::instance()->directory();

	TargetPath += sTarget;
	TargetPath += '\\';
	sTarget += ".cpp";
	TargetPath += sTarget;

	FILE* NFile;
	fopen_s(&NFile, TargetPath.c_str(), "wt");


	std::multiset<std::string>::iterator SIter = MapCpp.begin();
	std::multiset<std::string>::iterator EIter = MapCpp.end();


	for (; SIter != EIter; ++SIter)
	{
		std::string IncludePath = "#include <";
		IncludePath += SIter->c_str();
		IncludePath += ">\n" ;

		fprintf_s(NFile, IncludePath.c_str(), IncludePath.capacity());
	}

	fclose(NFile);
}