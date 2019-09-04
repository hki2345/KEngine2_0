#include "ComTest.h"
#include "KOne.h"

#include "KWindowManager.h"
#include "KInputManager.h"



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


	std::wstring Tmp = L"아아아아아아아앙";

	Tmp += std::to_wstring(Cnt);
	
	for (int i = 0; i < 100; i++)
	{
		TextOut(hdc, 1000, 0 + i * 10, Tmp.c_str(), (int)Tmp.size());
	}



	bool Value = KInputManager::instance()->is_press(VK_RIGHT);

	if (true == Value)
	{
		kone()->moving({ 100.0f, 0.0f });
	}

	Value = KInputManager::instance()->is_press(VK_LEFT);

	if (true == Value)
	{
		kone()->moving({ -100.0f, 0.0f });
	}

	Value = KInputManager::instance()->is_press(VK_UP);

	if (true == Value)
	{
		kone()->moving({ .0f, -100.0f });
	}

	Value = KInputManager::instance()->is_press(VK_DOWN);

	if (true == Value)
	{
		kone()->moving({ .0f, 100.0f });
	}

}

void ComTest::release()
{
	int a = 0;
}