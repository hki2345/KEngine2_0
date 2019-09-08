#include "IntroScene.h"
#include "GameManager.h"


#include <KText_Render.h>
#include <KBitMap_Render.h>
#include <KBitMap_Animator.h>

#include <KInputManager.h>

#include <KOne.h>



IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

void IntroScene::create()
{
	KScene::create();

	// create_backboard();
	create_star();
	create_circuschaley();
}

void IntroScene::update() 
{
	KScene::update();
	if (true == KInputManager::instance()->is_up(VK_SPACE))
	{
		GameManager::instance()->reset_game();
	}
}

void IntroScene::create_backboard()
{
	KOne* TOne = create_kone(L"BackBoard");
	TOne->size(KPos2(800, 600));

	KBitMap_Render* BITREN = TOne->add_component<KBitMap_Render>();
	BITREN->set_bit(L"Circus\\BackBoard.bmp", 0);
}

void IntroScene::create_star()
{
	float TSize = 20.0f;
	int Cnt = 0;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			if ((0 == x && 0 == y) || (15 == x && 0 == y) || 
				(0 == x && 7 == y) || (15 == x && 7 == y) ||
				((0 < x && 15 > x) && (0 < y && 7 > y)))
			{
				continue;
			}

			KOne* TOne = create_kone(L"Star");
			TOne->pos(KPos2(200.0f + x * (TSize + 5), 100.0f + y * TSize));
			TOne->size(KPos2(TSize, TSize));

			KBitMap_Animator* TRE = TOne->add_component<KBitMap_Animator>();

			std::vector<std::wstring> Tmp;
			Tmp.push_back(L"Circus\\star.bmp");
			Tmp.push_back(L"Circus\\star1.bmp");
			Tmp.push_back(L"Circus\\star2.bmp");
			TRE->insert_animation(L"Run", Tmp, 10, 0.1f, Cnt % 3);
			++Cnt;
		}
	}

}

void IntroScene::create_circuschaley()
{
	KOne* TOne = create_kone(L"Circus Chaley");
	TOne->pos(KPos2(400, 160));

	KText_Render* TREN = TOne->add_component<KText_Render>();
	TREN->set_text(L"서커스 찰리", L"DungGeunMo", 40, 10, RGB(97, 198, 233));



	TOne = create_kone(L"Game Start");
	TOne->pos(KPos2(400, 450));

	TREN = TOne->add_component<KText_Render>();
	TREN->set_text(L"게임 시작 - SPACE BAR", L"DungGeunMo", 40, 10);
}