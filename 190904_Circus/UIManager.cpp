#include "UIManager.h"
#include "ComPlayer.h"

#include <KTimeManager.h>

#include <KWindow.h>
#include <KScene.h>
#include <KOne.h>

#include <KText_Render.h>
#include <KBitMap_Render.h>


UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

void UIManager::create(KScene* _Scene, ComPlayer* _Player)
{
	pPlayer = _Player;
	create_wait(_Scene);
	create_game(_Scene);
	create_life(_Scene);

	for (int i = 0; i < VecWait.size(); i++)
	{
		VecWait[i]->active(false);
	}

	for (int i = 0; i < VecGame.size(); i++)
	{
		VecGame[i]->active(false);
	}

	for (int i = 0; i < LifeImage.size(); i++)
	{
		LifeImage[i]->active(false);
	}
}



void UIManager::create_wait(KScene* _Scene)
{
	VecWait.push_back(_Scene->create_kone(L"Stage Back"));
	VecWait[0]->size(pPlayer->kscene()->kwindow()->size());

	KBitMap_Render* TBR = VecWait[0]->add_component<KBitMap_Render>();
	TBR->set_bit(L"Circus\\BackBoard.bmp", 100, true);

	VecWait.push_back(_Scene->create_kone(L"Stage Letter"));
	VecWait[1]->pos({ 400.0f, 270.0f });

	KText_Render* TXR = VecWait[1]->add_component<KText_Render>();
	TXR->set_font(L"Stage 1", 20, 101, L"DungGeunMo");
}


void UIManager::create_game(KScene* _Scene)
{
	VecGame.push_back(_Scene->create_kone(L"Score Board"));
	VecGame[0]->size({ 780.0f, 60.0f });
	KBitMap_Render* TBR = VecGame[0]->add_component<KBitMap_Render>();
	TBR->set_bit(L"Circus\\ScoreBoard.bmp", 100);
	TBR->set_hold();


	int FontSize = 25;
	VecGame.push_back(_Scene->create_kone(L"Score Letter"));
	VecGame[1]->pos({ 200.0f, 20.0f });
	pScore = VecGame[1]->add_component<KText_Render>();
	pScore->set_font(L"1P-008450", FontSize, 101, L"DungGeunMo");
	pScore->set_hold();

	VecGame.push_back(_Scene->create_kone(L"Stage Letter"));
	VecGame[2]->pos({ 600.0f, 20.0f });
	KText_Render* TXR = VecGame[2]->add_component<KText_Render>();
	TXR->set_font(L"STAGE-01", FontSize, 101, L"DungGeunMo");
	TXR->set_hold();

	VecGame.push_back(_Scene->create_kone(L"BONUS Letter"));
	VecGame[3]->pos({ 380.0f, 20.0f });
	TXR = VecGame[3]->add_component<KText_Render>();
	TXR->set_font(L"BONUS", FontSize, 101, L"DungGeunMo", RGB(139,35,53));
	TXR->set_hold();


	VecGame.push_back(_Scene->create_kone(L"BONUS Letter"));
	VecGame[4]->pos({ 450.0f, 20.0f });
	pBonus = VecGame[4]->add_component<KText_Render>();
	pBonus->set_font(L"1234", FontSize, 101, L"DungGeunMo");
	pBonus->set_hold();
}



void UIManager::create_life(KScene* _Scene)
{
	for (int i = 0; i < 3; i++)
	{
		LifeImage.push_back(_Scene->create_kone(L"Score Board"));
		LifeImage[i]->size({ 15.0f, 15.0f });
		LifeImage[i]->pos({ 700.0f + i * 20, 20.0f });
		KBitMap_Render* TBR = LifeImage[i]->add_component<KBitMap_Render>();
		TBR->set_bit(L"Circus\\icon.bmp", 100);
		TBR->set_hold();
	}
}


void UIManager::set_wait()
{
	for (int i = 0; i < VecWait.size(); i++)
	{
		VecWait[i]->active(true);
	}
	for (int i = 0; i < VecGame.size(); i++)
	{
		
		VecGame[i]->active(false);
	}

	for (int i = 0; i < LifeImage.size(); i++)
	{
		LifeImage[i]->active(false);
	}

	BonusScore = 5000;
	MinusBonus = .5f;
	MinusBonusScoreDelta = .0f;
}

void UIManager::set_game()
{
	if (bSetGame == false)
	{
		bSetGame = true;
	}

	for (int i = 0; i < VecWait.size(); i++)
	{
		VecWait[i]->active(false);
	}
	for (int i = 0; i < VecGame.size(); i++)
	{
		VecGame[i]->active(true);
	}
	for (int i = 0; i < pPlayer->score_info().Life; i++)
	{
		LifeImage[i]->active(true);
	}
}

void UIManager::update_gameUI()
{
	if (false == pPlayer->check_acting())
	{
		return;
	}

	MinusBonusScoreDelta += KTimeManager::instance()->deltatime();
	if (MinusBonusScoreDelta >= MinusBonus)
	{
		MinusBonusScoreDelta = .0f;
		BonusScore -= 10;
	}


	int FontSize = 25;

	std::wstring Tmp = L"1P-00";
	Tmp += std::to_wstring(pPlayer->score_info().Score);
	pScore->set_text(Tmp.c_str());

	Tmp.clear();
	Tmp = std::to_wstring(BonusScore);
	pBonus->set_text(Tmp.c_str());
}