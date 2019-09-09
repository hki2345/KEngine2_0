#include "KPathManager.h"
#include <direct.h>
#include <stdlib.h>
#include <iostream>
#include <io.h>
#include <fstream>

#include "KMacro.h"


KPathManager* KPathManager::pKPathManager = nullptr;


void KPathManager::init()
{
	wchar_t tmpAllpath[KNAMING] = { 0, };
	wchar_t tmpDrive[KNAMING] = { 0, };
	wchar_t tmpDirectory[KNAMING] = { 0, };
	wchar_t tmpFileName[KNAMING] = { 0, };
	wchar_t tmpExe[KNAMING] = { 0, };

	_wgetcwd(tmpAllpath, KNAMING);
	_wsplitpath_s(tmpAllpath, tmpDrive, tmpDirectory, tmpFileName, tmpExe);


	mAllpath = tmpAllpath;
	mDrive = tmpDrive;
	mDirectory = tmpDirectory;
	mFileName = tmpFileName;
	mExtension = tmpExe;
}

void KPathManager::release()
{
	mAllpath.clear();
	mDrive.clear();
	mDirectory.clear();
	mFileName.clear();
	mExtension.clear();

	RELEASE_PTR(pKPathManager);
}


void KPathManager::char_towchar(wchar_t* _Target, char* _Source)
{
	size_t newsize = strlen(_Source) + 1;
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, _Target, newsize, _Source, _TRUNCATE);
}


std::vector<KResourcePath> KPathManager::load_totargetfolder(
	const wchar_t* _Folder, 
	const wchar_t* _Extension)
{
	std::wstring TargetPath = KPathManager::instance()->all_path();
	TargetPath += L'\\';
	TargetPath += _Folder;


	std::wstring FolderPath = _Folder;


	std::vector< KResourcePath> PathVecTmp;


	struct _wfinddata_t FD;
	intptr_t Handle;

	TargetPath += L'\\';
	TargetPath += L"*.*";

	Handle = _wfindfirst(TargetPath.c_str(), &FD);


	while (0 == _wfindnext(Handle, &FD))
	{
		std::wstring Name = FD.name;
		// ���� ��θ� ��Ȯ�� ���ؾ� �� �� �ְ� �ռ� ����������
		/*if (-1 == (int)Name.find(L"."))
		{
			FolderPath += L"\\";
			FolderPath += Name;
			continue;
		}*/

		if (-1 != (int)Name.find(_Extension))
		{
			PathVecTmp.push_back(KResourcePath({ FolderPath, Name }));
		}
	}

	_findclose(Handle);

	return PathVecTmp;
}


bool KPathManager::input_wchar(wchar_t* _Target, const int& _Target_sizeof, const wchar_t* _Path)
{
	memset(_Target, 0, _Target_sizeof);

	int MaxIdx = (int)(_Target_sizeof * .5f) - 1;
	int idx = (int)wcslen(_Path);

	if (MaxIdx > idx)
	{
		for (int i = 0; i < idx; ++i)
		{
			_Target[i] = _Path[i];
		}
	}
	else
	{
		for (int i = 0; i < MaxIdx; ++i)
		{
			_Target[i] = _Path[i];
		}
	}

	return true;
}


std::vector<std::wstring> KPathManager::vec_loadline(const wchar_t* _Path)
{
	std::vector<std::wstring> Tmp;
	wchar_t Arr[256];

	std::wifstream ifs(_Path, std::ios::in | std::ios::binary);
	std::locale loc("KOR");
	ifs.imbue(loc);
	
	while (!ifs.eof())
	{
		ifs.getline(Arr, 256);
		Tmp.push_back(Arr);
	}
	
	ifs.close();

	return Tmp;
}



std::vector<std::wstring> KPathManager::split_line(wchar_t* _Path, const std::wstring& _Split /*= L" ,\t\n"*/)
{
	std::vector<std::wstring> Tmp;
	
	wchar_t* tok = nullptr;
	wchar_t* ntok = nullptr;

	tok = wcstok_s(_Path, _Split.c_str(), &ntok);

	while (tok != NULL)
	{
		// While there are tokens in "string"
		Tmp.push_back(tok);

		// Get next token:
		tok = wcstok_s(NULL, _Split.c_str(), &ntok);
	}

	return Tmp;
}



std::vector<std::wstring> KPathManager::split_line(
	const std::vector<std::wstring>& _Vec,
	const std::wstring& _Split /*= L" ,\t\n"*/,
	const int& idx /*= 0*/)
{
	wchar_t* Tmp = new wchar_t[_Vec[idx].size()];
	wcscpy_s(Tmp, _Vec[idx].size(), _Vec[idx].c_str());
	return split_line(Tmp, _Split);
}