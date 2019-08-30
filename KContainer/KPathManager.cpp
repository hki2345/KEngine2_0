#include "KPathManager.h"
#include <direct.h>
#include <stdlib.h>

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
	mExe = tmpExe;
}

void KPathManager::release()
{
	mAllpath.clear();
	mDrive.clear();
	mDirectory.clear();
	mFileName.clear();
	mExe.clear();

	RELEASE_PTR(pKPathManager);
}


bool KPathManager::input_wchar(wchar_t* _Target, const int& _Sizeof, const wchar_t* _Path)
{
	memset(_Target, 0, _Sizeof);

	int MaxIdx = (int)(_Sizeof * .5f) - 1;
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