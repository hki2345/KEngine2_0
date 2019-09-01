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
	return true;
}

HDC& KBitMap::size(const KSize2& _Size)
{
	MyBitMap = CreateCompatibleBitmap(KWindowManager::instance()->main_hdc(), _Size.ix, _Size.iy);
	OldBitmap = (HBITMAP)SelectObject(MyDC, MyBitMap);
	GetObjectW(MyBitMap, sizeof(BITMAP), &BitMapData);

	return MyDC;
}

bool KBitMap::load()
{
	MyBitMap = (HBITMAP)LoadImageW(
		KWindowManager::instance()->hinstance(), L"TEst", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	GetObjectW(MyBitMap, sizeof(BITMAP), &BitMapData);
	return true;
}
bool KBitMap::save()
{
	return true;
}
