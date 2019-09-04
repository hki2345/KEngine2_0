#include "KBitMap.h"
#include "KWindowManager.h"

#include <KPathManager.h>


KBitMap::KBitMap()
{
}


KBitMap::~KBitMap()
{
	DeleteDC(MyDC);
	DeleteObject(OldBitmap);
}




bool KBitMap::create(const wchar_t* _Folder, const wchar_t* _Name)
{
	KResource::sName = _Name;
	KResource::sPath = _Folder;

	MyDC = CreateCompatibleDC(KWindowManager::instance()->main_hdc());
	
	if (L"KCore" != _Folder)
	{
		MyBitMap = (HBITMAP)LoadImage(NULL, KResource::sName.c_str(), IMAGE_BITMAP
			, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		OldBitmap = (HBITMAP)SelectObject(MyDC, MyBitMap);
		GetObjectW(MyBitMap, sizeof(BITMAP), &BitMapData);
	}

	return true;
}

HDC& KBitMap::kwindow_size(const KSize2& _Size)
{
	MyBitMap = CreateCompatibleBitmap(KWindowManager::instance()->main_hdc(), (int)_Size.x, (int)_Size.y);
	OldBitmap = (HBITMAP)SelectObject(MyDC, MyBitMap);
	GetObjectW(MyBitMap, sizeof(BITMAP), &BitMapData);

	return MyDC;
}

bool KBitMap::load()
{
	MyBitMap = (HBITMAP)LoadImageW(
		KWindowManager::instance()->hinstance(), L"Test.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	GetObjectW(MyBitMap, sizeof(BITMAP), &BitMapData);
	return true;
}
bool KBitMap::save()
{
	return true;
}

KPos2 KBitMap::size()
{
	return KPos2((float)BitMapData.bmWidth, (float)BitMapData.bmHeight);
}