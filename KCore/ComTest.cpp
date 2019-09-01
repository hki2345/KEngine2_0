#include "ComTest.h"
#include "KWindowManager.h"




ComTest::ComTest()
{
	int a = 0;
}


ComTest::~ComTest()
{
	int a = 0;
}

bool ComTest::init()
{
	Cnt = 0;
	return true;
}
void ComTest::update()
{
	++Cnt;
	HDC hdc = KWindowManager::instance()->back_hdc();


	std::wstring Tmp = L"COM";

	Tmp += std::to_wstring(Cnt);

	TextOut(hdc, 1000, 800, Tmp.c_str(), (int)Tmp.size());
	ReleaseDC(KWindowManager::instance()->main_hwnd(), hdc);
}

void ComTest::release()
{
	int a = 0;
}