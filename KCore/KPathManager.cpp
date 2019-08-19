#include "KPathManager.h"
#include <direct.h>
#include <stdlib.h>



wchar_t KPathManager::mAllpath[KNAMING] = { 0, };
wchar_t KPathManager::mDrive[KNAMING] = { 0, };
wchar_t KPathManager::mDirectory[KNAMING] = { 0, };
wchar_t KPathManager::mFileName[KNAMING] = { 0, };
wchar_t KPathManager::mExe[KNAMING] = { 0, };

void KPathManager::init()
{
	_wgetcwd(mAllpath, KNAMING);
	_wsplitpath_s(mAllpath, mDrive, mDirectory, mFileName, mExe);
}