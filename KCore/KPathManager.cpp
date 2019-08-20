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